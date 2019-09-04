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
typedef  scalar_t__ u64 ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MAP_EQ ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_B ; 
 int mthca_cmd (struct mthca_dev*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,char*,unsigned long long,int) ; 

int mthca_MAP_EQ(struct mthca_dev *dev, u64 event_mask, int unmap,
		 int eq_num)
{
	mthca_dbg(dev, "%s mask %016llx for eqn %d\n",
		  unmap ? "Clearing" : "Setting",
		  (unsigned long long) event_mask, eq_num);
	return mthca_cmd(dev, event_mask, (unmap << 31) | eq_num,
			 0, CMD_MAP_EQ, CMD_TIME_CLASS_B);
}