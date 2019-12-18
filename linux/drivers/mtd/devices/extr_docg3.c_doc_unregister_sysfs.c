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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct docg3_cascade {scalar_t__* floors; } ;

/* Variables and functions */
 int DOC_MAX_NBFLOORS ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** doc_sys_attrs ; 

__attribute__((used)) static void doc_unregister_sysfs(struct platform_device *pdev,
				 struct docg3_cascade *cascade)
{
	struct device *dev = &pdev->dev;
	int floor, i;

	for (floor = 0; floor < DOC_MAX_NBFLOORS && cascade->floors[floor];
	     floor++)
		for (i = 0; i < 4; i++)
			device_remove_file(dev, &doc_sys_attrs[floor][i]);
}