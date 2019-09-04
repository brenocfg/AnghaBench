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
struct device {int dummy; } ;
struct cec_devnode {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_devnode_lock ; 
 int /*<<< orphan*/  cec_devnode_nums ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_cec_adapter (struct cec_devnode*) ; 
 struct cec_devnode* to_cec_devnode (struct device*) ; 

__attribute__((used)) static void cec_devnode_release(struct device *cd)
{
	struct cec_devnode *devnode = to_cec_devnode(cd);

	mutex_lock(&cec_devnode_lock);
	/* Mark device node number as free */
	clear_bit(devnode->minor, cec_devnode_nums);
	mutex_unlock(&cec_devnode_lock);

	cec_delete_adapter(to_cec_adapter(devnode));
}