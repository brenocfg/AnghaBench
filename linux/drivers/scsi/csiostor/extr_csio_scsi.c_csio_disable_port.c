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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct csio_lnode {int /*<<< orphan*/  portid; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  csio_disable_lnodes (struct csio_hw*,int /*<<< orphan*/ ,int) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lnodes_block_by_port (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_lnodes_unblock_by_port (struct csio_hw*,int /*<<< orphan*/ ) ; 
 struct csio_lnode* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
csio_disable_port(struct device *dev,
		   struct device_attribute *attr, const char *buf, size_t count)
{
	struct csio_lnode *ln = shost_priv(class_to_shost(dev));
	struct csio_hw *hw = csio_lnode_to_hw(ln);
	bool disable;

	if (*buf == '1' || *buf == '0')
		disable = (*buf == '1') ? true : false;
	else
		return -EINVAL;

	/* Block upper IOs */
	csio_lnodes_block_by_port(hw, ln->portid);

	spin_lock_irq(&hw->lock);
	csio_disable_lnodes(hw, ln->portid, disable);
	spin_unlock_irq(&hw->lock);

	/* Unblock upper IOs */
	csio_lnodes_unblock_by_port(hw, ln->portid);
	return count;
}