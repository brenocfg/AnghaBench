#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int flags; } ;
struct mthca_dev {TYPE_1__ cmd; } ;

/* Variables and functions */
 int MTHCA_CMD_USE_EVENTS ; 
 int mthca_cmd_poll (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int mthca_cmd_wait (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mthca_cmd_box(struct mthca_dev *dev,
			 u64 in_param,
			 u64 out_param,
			 u32 in_modifier,
			 u8 op_modifier,
			 u16 op,
			 unsigned long timeout)
{
	if (dev->cmd.flags & MTHCA_CMD_USE_EVENTS)
		return mthca_cmd_wait(dev, in_param, &out_param, 0,
				      in_modifier, op_modifier, op,
				      timeout);
	else
		return mthca_cmd_poll(dev, in_param, &out_param, 0,
				      in_modifier, op_modifier, op,
				      timeout);
}