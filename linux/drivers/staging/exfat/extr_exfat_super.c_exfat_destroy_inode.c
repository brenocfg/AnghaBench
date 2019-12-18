#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * target; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_I (struct inode*) ; 
 int /*<<< orphan*/  exfat_inode_cachep ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void exfat_destroy_inode(struct inode *inode)
{
	kfree(EXFAT_I(inode)->target);
	EXFAT_I(inode)->target = NULL;

	kmem_cache_free(exfat_inode_cachep, EXFAT_I(inode));
}