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
struct recurse_struct {int /*<<< orphan*/  fn; struct parse_tree_data* obj; } ;
struct parse_tree_data {int index; struct device* dev; struct hardware_path* modpath; } ;
struct hardware_path {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_parent ; 
 int /*<<< orphan*/  descend_children ; 
 scalar_t__ device_for_each_child (struct device*,struct recurse_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *
parse_tree_node(struct device *parent, int index, struct hardware_path *modpath)
{
	struct parse_tree_data d = {
		.index          = index,
		.modpath        = modpath,
	};

	struct recurse_struct recurse_data = {
		.obj	= &d,
		.fn	= check_parent,
	};

	if (device_for_each_child(parent, &recurse_data, descend_children))
		/* nothing */;

	return d.dev;
}