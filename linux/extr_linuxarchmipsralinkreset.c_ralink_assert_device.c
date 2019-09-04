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
typedef  int /*<<< orphan*/  u32 ;
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned long) ; 
 int /*<<< orphan*/  SYSC_REG_RESET_CTRL ; 
 int /*<<< orphan*/  rt_sysc_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_sysc_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ralink_assert_device(struct reset_controller_dev *rcdev,
				unsigned long id)
{
	u32 val;

	if (id < 8)
		return -1;

	val = rt_sysc_r32(SYSC_REG_RESET_CTRL);
	val |= BIT(id);
	rt_sysc_w32(val, SYSC_REG_RESET_CTRL);

	return 0;
}