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
struct pnp_dev {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_clean_resource_table (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_res_mutex ; 
 int pnp_stop_dev (struct pnp_dev*) ; 

int pnp_disable_dev(struct pnp_dev *dev)
{
	int error;

	if (!dev->active)
		return 0;

	error = pnp_stop_dev(dev);
	if (error)
		return error;

	dev->active = 0;

	/* release the resources so that other devices can use them */
	mutex_lock(&pnp_res_mutex);
	pnp_clean_resource_table(dev);
	mutex_unlock(&pnp_res_mutex);

	return 0;
}