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
struct transport_container {int dummy; } ;
struct raid_data {int /*<<< orphan*/  component_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct raid_data*) ; 
 struct raid_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raid_setup(struct transport_container *tc, struct device *dev,
		       struct device *cdev)
{
	struct raid_data *rd;

	BUG_ON(dev_get_drvdata(cdev));

	rd = kzalloc(sizeof(*rd), GFP_KERNEL);
	if (!rd)
		return -ENOMEM;

	INIT_LIST_HEAD(&rd->component_list);
	dev_set_drvdata(cdev, rd);
		
	return 0;
}