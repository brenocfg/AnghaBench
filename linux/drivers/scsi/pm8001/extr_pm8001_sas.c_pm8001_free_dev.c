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
struct pm8001_device {int /*<<< orphan*/ * sas_device; int /*<<< orphan*/  device_id; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_MAX_DEVICES ; 
 int /*<<< orphan*/  SAS_PHY_UNUSED ; 
 int /*<<< orphan*/  memset (struct pm8001_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pm8001_free_dev(struct pm8001_device *pm8001_dev)
{
	u32 id = pm8001_dev->id;
	memset(pm8001_dev, 0, sizeof(*pm8001_dev));
	pm8001_dev->id = id;
	pm8001_dev->dev_type = SAS_PHY_UNUSED;
	pm8001_dev->device_id = PM8001_MAX_DEVICES;
	pm8001_dev->sas_device = NULL;
}