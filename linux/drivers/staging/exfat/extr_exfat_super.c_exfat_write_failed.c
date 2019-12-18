#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {scalar_t__ size; } ;
struct TYPE_4__ {TYPE_1__ fid; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_I (struct inode*) ; 
 int /*<<< orphan*/  exfat_truncate (struct inode*,scalar_t__) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 

__attribute__((used)) static void exfat_write_failed(struct address_space *mapping, loff_t to)
{
	struct inode *inode = mapping->host;

	if (to > i_size_read(inode)) {
		truncate_pagecache(inode, i_size_read(inode));
		EXFAT_I(inode)->fid.size = i_size_read(inode);
		exfat_truncate(inode, i_size_read(inode));
	}
}