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
struct exynos_drm_ipp {int task; int /*<<< orphan*/  head; int /*<<< orphan*/  todo_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void exynos_drm_ipp_unregister(struct device *dev,
			       struct exynos_drm_ipp *ipp)
{
	WARN_ON(ipp->task);
	WARN_ON(!list_empty(&ipp->todo_list));
	list_del(&ipp->head);
}