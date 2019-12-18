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
struct rc_scancode_filter {int data; int mask; } ;
struct img_ir_filter {unsigned int data; unsigned int mask; } ;

/* Variables and functions */

__attribute__((used)) static int img_ir_jvc_filter(const struct rc_scancode_filter *in,
			     struct img_ir_filter *out, u64 protocols)
{
	unsigned int cust, data;
	unsigned int cust_m, data_m;

	cust   = (in->data >> 8) & 0xff;
	cust_m = (in->mask >> 8) & 0xff;
	data   = (in->data >> 0) & 0xff;
	data_m = (in->mask >> 0) & 0xff;

	out->data = cust   | data << 8;
	out->mask = cust_m | data_m << 8;

	return 0;
}