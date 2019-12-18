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
struct venc_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void venc_runtime_put(struct venc_device *venc)
{
	int r;

	DSSDBG("venc_runtime_put\n");

	r = pm_runtime_put_sync(&venc->pdev->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
}