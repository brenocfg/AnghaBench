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
struct sun4i_frontend {int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sun4i_frontend* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_force_suspend (struct device*) ; 

__attribute__((used)) static void sun4i_frontend_unbind(struct device *dev, struct device *master,
			    void *data)
{
	struct sun4i_frontend *frontend = dev_get_drvdata(dev);

	list_del(&frontend->list);
	pm_runtime_force_suspend(dev);
}