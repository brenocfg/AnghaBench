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
struct etm_drvdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int etm_get_trace_id (struct etm_drvdata*) ; 

__attribute__((used)) static int etm_trace_id(struct coresight_device *csdev)
{
	struct etm_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	return etm_get_trace_id(drvdata);
}