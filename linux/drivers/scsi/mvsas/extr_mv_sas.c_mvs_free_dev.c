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
struct mvs_device {int /*<<< orphan*/  taskfileset; int /*<<< orphan*/  dev_status; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVS_DEV_NORMAL ; 
 int /*<<< orphan*/  MVS_ID_NOT_MAPPED ; 
 int /*<<< orphan*/  SAS_PHY_UNUSED ; 
 int /*<<< orphan*/  memset (struct mvs_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvs_free_dev(struct mvs_device *mvi_dev)
{
	u32 id = mvi_dev->device_id;
	memset(mvi_dev, 0, sizeof(*mvi_dev));
	mvi_dev->device_id = id;
	mvi_dev->dev_type = SAS_PHY_UNUSED;
	mvi_dev->dev_status = MVS_DEV_NORMAL;
	mvi_dev->taskfileset = MVS_ID_NOT_MAPPED;
}