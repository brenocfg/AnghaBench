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
struct sm501_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/  list; } ;
struct sm501_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sm501_remove_sub(struct sm501_devdata *sm,
			     struct sm501_device *smdev)
{
	list_del(&smdev->list);
	platform_device_unregister(&smdev->pdev);
}