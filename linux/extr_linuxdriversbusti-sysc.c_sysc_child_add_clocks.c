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
struct sysc {int nr_clocks; int /*<<< orphan*/ * clock_roles; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int sysc_child_add_named_clock (struct sysc*,struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_child_add_clocks(struct sysc *ddata,
				 struct device *child)
{
	int i, error;

	for (i = 0; i < ddata->nr_clocks; i++) {
		error = sysc_child_add_named_clock(ddata,
						   child,
						   ddata->clock_roles[i]);
		if (error && error != -EEXIST) {
			dev_err(ddata->dev, "could not add child clock %s: %i\n",
				ddata->clock_roles[i], error);

			return error;
		}
	}

	return 0;
}