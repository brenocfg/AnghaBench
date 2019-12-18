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
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int syscfg_reset_program_hw (struct reset_controller_dev*,unsigned long,int) ; 

__attribute__((used)) static int syscfg_reset_deassert(struct reset_controller_dev *rcdev,
				 unsigned long idx)
{
	return syscfg_reset_program_hw(rcdev, idx, false);
}