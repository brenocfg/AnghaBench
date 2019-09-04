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
typedef  int /*<<< orphan*/  u32 ;
struct tpiu_drvdata {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct tpiu_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tpiu_enable_hw (struct tpiu_drvdata*) ; 

__attribute__((used)) static int tpiu_enable(struct coresight_device *csdev, u32 mode)
{
	struct tpiu_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	tpiu_enable_hw(drvdata);

	dev_info(drvdata->dev, "TPIU enabled\n");
	return 0;
}