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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bits_magic ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  read_bitstream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int readmagic_bitstream(u8 *bitdata, int *offset)
{
	u8 buf[13];
	int r;

	read_bitstream(bitdata, buf, offset, 13);
	r = memcmp(buf, bits_magic, 13);
	if (r) {
		pr_err("error: corrupted header\n");
		return -EINVAL;
	}
	pr_info("bitstream file magic number Ok\n");

	*offset = 13;	/* magic length */

	return 0;
}