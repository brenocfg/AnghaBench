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
struct opp_table {int /*<<< orphan*/  dev_list; } ;
struct opp_device {int /*<<< orphan*/  node; struct device const* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct opp_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opp_debug_register (struct opp_device*,struct opp_table*) ; 

__attribute__((used)) static struct opp_device *_add_opp_dev_unlocked(const struct device *dev,
						struct opp_table *opp_table)
{
	struct opp_device *opp_dev;

	opp_dev = kzalloc(sizeof(*opp_dev), GFP_KERNEL);
	if (!opp_dev)
		return NULL;

	/* Initialize opp-dev */
	opp_dev->dev = dev;

	list_add(&opp_dev->node, &opp_table->dev_list);

	/* Create debugfs entries for the opp_table */
	opp_debug_register(opp_dev, opp_table);

	return opp_dev;
}