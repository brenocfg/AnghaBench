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
struct inode {scalar_t__ i_private; } ;
struct file {scalar_t__ private_data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAM_DEV_FWCACHE_FLUSH ; 
 int /*<<< orphan*/  t4_fwcache (struct adapter*,int /*<<< orphan*/ ) ; 

int mem_open(struct inode *inode, struct file *file)
{
	unsigned int mem;
	struct adapter *adap;

	file->private_data = inode->i_private;

	mem = (uintptr_t)file->private_data & 0x7;
	adap = file->private_data - mem;

	(void)t4_fwcache(adap, FW_PARAM_DEV_FWCACHE_FLUSH);

	return 0;
}