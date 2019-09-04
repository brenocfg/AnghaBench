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
typedef  int /*<<< orphan*/  u64 ;
struct bitstream {int dummy; } ;

/* Variables and functions */
 int __vli_encode_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bitstream_put_bits (struct bitstream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  code ; 

__attribute__((used)) static inline int vli_encode_bits(struct bitstream *bs, u64 in)
{
	u64 code = code;
	int bits = __vli_encode_bits(&code, in);

	if (bits <= 0)
		return bits;

	return bitstream_put_bits(bs, code, bits);
}