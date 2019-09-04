#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rand_data {unsigned int data; } ;
typedef  unsigned int __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 unsigned int DATA_SIZE_BITS ; 
 unsigned int jent_rol64 (unsigned int,int) ; 

__attribute__((used)) static void jent_stir_pool(struct rand_data *entropy_collector)
{
	/*
	 * to shut up GCC on 32 bit, we have to initialize the 64 variable
	 * with two 32 bit variables
	 */
	union c {
		__u64 u64;
		__u32 u32[2];
	};
	/*
	 * This constant is derived from the first two 32 bit initialization
	 * vectors of SHA-1 as defined in FIPS 180-4 section 5.3.1
	 */
	union c constant;
	/*
	 * The start value of the mixer variable is derived from the third
	 * and fourth 32 bit initialization vector of SHA-1 as defined in
	 * FIPS 180-4 section 5.3.1
	 */
	union c mixer;
	unsigned int i = 0;

	/*
	 * Store the SHA-1 constants in reverse order to make up the 64 bit
	 * value -- this applies to a little endian system, on a big endian
	 * system, it reverses as expected. But this really does not matter
	 * as we do not rely on the specific numbers. We just pick the SHA-1
	 * constants as they have a good mix of bit set and unset.
	 */
	constant.u32[1] = 0x67452301;
	constant.u32[0] = 0xefcdab89;
	mixer.u32[1] = 0x98badcfe;
	mixer.u32[0] = 0x10325476;

	for (i = 0; i < DATA_SIZE_BITS; i++) {
		/*
		 * get the i-th bit of the input random number and only XOR
		 * the constant into the mixer value when that bit is set
		 */
		if ((entropy_collector->data >> i) & 1)
			mixer.u64 ^= constant.u64;
		mixer.u64 = jent_rol64(mixer.u64, 1);
	}
	entropy_collector->data ^= mixer.u64;
}