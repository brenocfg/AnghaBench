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
struct opp_table {int dummy; } ;
struct opp_device {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct opp_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opp_debug_unregister (struct opp_device*,struct opp_table*) ; 

__attribute__((used)) static void _remove_opp_dev(struct opp_device *opp_dev,
			    struct opp_table *opp_table)
{
	opp_debug_unregister(opp_dev, opp_table);
	list_del(&opp_dev->node);
	kfree(opp_dev);
}