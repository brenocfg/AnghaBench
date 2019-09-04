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
struct unicam_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int unicam_runtime_get(struct unicam_device *dev)
{
	int r;

	r = pm_runtime_get_sync(&dev->pdev->dev);

	return r;
}