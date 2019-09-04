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
struct master {int /*<<< orphan*/  dev; } ;
struct component {int bound; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unbind ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ ,struct component*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void component_unbind(struct component *component,
	struct master *master, void *data)
{
	WARN_ON(!component->bound);

	component->ops->unbind(component->dev, master->dev, data);
	component->bound = false;

	/* Release all resources claimed in the binding of this component */
	devres_release_group(component->dev, component);
}