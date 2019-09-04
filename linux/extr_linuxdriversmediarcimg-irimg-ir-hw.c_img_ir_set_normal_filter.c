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
struct rc_scancode_filter {int dummy; } ;
struct rc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_FILTER_NORMAL ; 
 int img_ir_set_filter (struct rc_dev*,int /*<<< orphan*/ ,struct rc_scancode_filter*) ; 

__attribute__((used)) static int img_ir_set_normal_filter(struct rc_dev *dev,
				    struct rc_scancode_filter *sc_filter)
{
	return img_ir_set_filter(dev, RC_FILTER_NORMAL, sc_filter);
}