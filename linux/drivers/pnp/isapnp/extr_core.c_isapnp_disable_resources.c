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
struct pnp_dev {scalar_t__ active; int /*<<< orphan*/  number; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  isapnp_cfg_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isapnp_cfg_end () ; 
 int /*<<< orphan*/  isapnp_deactivate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isapnp_disable_resources(struct pnp_dev *dev)
{
	if (!dev->active)
		return -EINVAL;
	isapnp_cfg_begin(dev->card->number, dev->number);
	isapnp_deactivate(dev->number);
	dev->active = 0;
	isapnp_cfg_end();
	return 0;
}