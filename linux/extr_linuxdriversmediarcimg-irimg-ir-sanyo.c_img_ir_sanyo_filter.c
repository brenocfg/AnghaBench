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
typedef  int u64 ;
struct rc_scancode_filter {int data; int mask; } ;
struct img_ir_filter {int data; int mask; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int img_ir_sanyo_filter(const struct rc_scancode_filter *in,
			       struct img_ir_filter *out, u64 protocols)
{
	unsigned int addr, addr_inv, data, data_inv;
	unsigned int addr_m, data_m;

	data = in->data & 0xff;
	data_m = in->mask & 0xff;
	data_inv = data ^ 0xff;

	if (in->data & 0xff700000)
		return -EINVAL;

	addr       = (in->data >> 8) & 0x1fff;
	addr_m     = (in->mask >> 8) & 0x1fff;
	addr_inv   = addr ^ 0x1fff;

	out->data = (u64)data_inv << 34 |
		    (u64)data     << 26 |
			 addr_inv << 13 |
			 addr;
	out->mask = (u64)data_m << 34 |
		    (u64)data_m << 26 |
			 addr_m << 13 |
			 addr_m;
	return 0;
}