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
struct inode {int dummy; } ;
struct exfat_inode_info {char* target; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 struct exfat_inode_info* EXFAT_I (struct inode*) ; 

__attribute__((used)) static const char *exfat_get_link(struct dentry *dentry, struct inode *inode,
				  struct delayed_call *done)
{
	struct exfat_inode_info *ei = EXFAT_I(inode);

	if (ei->target) {
		char *cookie = ei->target;

		if (cookie)
			return (char *)(ei->target);
	}
	return NULL;
}