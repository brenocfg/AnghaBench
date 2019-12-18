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
struct srp_target_port {int /*<<< orphan*/  mr_pool_size; TYPE_1__* srp_host; } ;
struct srp_fr_pool {int dummy; } ;
struct srp_device {int /*<<< orphan*/  max_pages_per_mr; int /*<<< orphan*/  pd; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct srp_device* srp_dev; } ;

/* Variables and functions */
 struct srp_fr_pool* srp_create_fr_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct srp_fr_pool *srp_alloc_fr_pool(struct srp_target_port *target)
{
	struct srp_device *dev = target->srp_host->srp_dev;

	return srp_create_fr_pool(dev->dev, dev->pd, target->mr_pool_size,
				  dev->max_pages_per_mr);
}