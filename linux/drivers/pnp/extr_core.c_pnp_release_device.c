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
struct pnp_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_free_ids (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_free_options (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_free_resources (struct pnp_dev*) ; 
 struct pnp_dev* to_pnp_dev (struct device*) ; 

__attribute__((used)) static void pnp_release_device(struct device *dmdev)
{
	struct pnp_dev *dev = to_pnp_dev(dmdev);

	pnp_free_ids(dev);
	pnp_free_resources(dev);
	pnp_free_options(dev);
	kfree(dev);
}