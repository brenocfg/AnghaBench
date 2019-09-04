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
struct rc_scancode_filter {int dummy; } ;
struct img_ir_filter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int img_ir_rc5_filter(const struct rc_scancode_filter *in,
				 struct img_ir_filter *out, u64 protocols)
{
	/* Not supported by the hw. */
	return -EINVAL;
}