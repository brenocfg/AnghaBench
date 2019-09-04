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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int SHA256_BLOCK_SIZE ; 
 size_t SHA256_LOG2_BLOCK_SIZE ; 
 int SHA256_PADLENGTHFIELD_SIZE ; 
 int cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

inline uint32_t sha256_pad(uint8_t padblock[SHA256_BLOCK_SIZE * 2],
			 uint64_t total_len)
{
	uint32_t i = total_len & (SHA256_BLOCK_SIZE - 1);

	memset(&padblock[i], 0, SHA256_BLOCK_SIZE);
	padblock[i] = 0x80;

	i += ((SHA256_BLOCK_SIZE - 1) &
	      (0 - (total_len + SHA256_PADLENGTHFIELD_SIZE + 1)))
	     + 1 + SHA256_PADLENGTHFIELD_SIZE;

#if SHA256_PADLENGTHFIELD_SIZE == 16
	*((uint64_t *) &padblock[i - 16]) = 0;
#endif

	*((uint64_t *) &padblock[i - 8]) = cpu_to_be64(total_len << 3);

	/* Number of extra blocks to hash */
	return i >> SHA256_LOG2_BLOCK_SIZE;
}