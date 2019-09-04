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
struct etmv4_drvdata {int cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etm4_cpu_id(struct coresight_device *csdev)
{
	struct etmv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	return drvdata->cpu;
}