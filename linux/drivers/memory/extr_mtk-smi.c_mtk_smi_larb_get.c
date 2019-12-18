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

/* Variables and functions */
 int pm_runtime_get_sync (struct device*) ; 

int mtk_smi_larb_get(struct device *larbdev)
{
	int ret = pm_runtime_get_sync(larbdev);

	return (ret < 0) ? ret : 0;
}