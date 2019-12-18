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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_MINORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cap_class ; 
 int /*<<< orphan*/  cap_dev_num ; 
 int /*<<< orphan*/  class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 

int cap_init(void)
{
	int ret;

	cap_class = class_create(THIS_MODULE, "gb_authenticate");
	if (IS_ERR(cap_class))
		return PTR_ERR(cap_class);

	ret = alloc_chrdev_region(&cap_dev_num, 0, NUM_MINORS,
				  "gb_authenticate");
	if (ret)
		goto err_remove_class;

	return 0;

err_remove_class:
	class_destroy(cap_class);
	return ret;
}