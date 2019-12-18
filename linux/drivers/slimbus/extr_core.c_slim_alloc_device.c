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
struct slim_eaddr {int dummy; } ;
struct slim_device {int /*<<< orphan*/  dev; struct slim_eaddr e_addr; } ;
struct slim_controller {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct slim_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int slim_add_device (struct slim_controller*,struct slim_device*,struct device_node*) ; 

__attribute__((used)) static struct slim_device *slim_alloc_device(struct slim_controller *ctrl,
					     struct slim_eaddr *eaddr,
					     struct device_node *node)
{
	struct slim_device *sbdev;
	int ret;

	sbdev = kzalloc(sizeof(*sbdev), GFP_KERNEL);
	if (!sbdev)
		return NULL;

	sbdev->e_addr = *eaddr;
	ret = slim_add_device(ctrl, sbdev, node);
	if (ret) {
		put_device(&sbdev->dev);
		return NULL;
	}

	return sbdev;
}