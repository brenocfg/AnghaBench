#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_2__ dispc ; 
 int pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

void dispc_runtime_put(void)
{
	int r;

	DSSDBG("dispc_runtime_put\n");

	r = pm_runtime_put_sync(&dispc.pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
}