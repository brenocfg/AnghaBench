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
struct dispc_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

int dispc_runtime_get(struct dispc_device *dispc)
{
	int r;

	DSSDBG("dispc_runtime_get\n");

	r = pm_runtime_get_sync(&dispc->pdev->dev);
	WARN_ON(r < 0);
	return r < 0 ? r : 0;
}