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
struct xrcd_table_entry {struct ib_xrcd* xrcd; } ;
struct inode {int dummy; } ;
struct ib_xrcd {int dummy; } ;
struct ib_uverbs_device {int dummy; } ;

/* Variables and functions */
 struct xrcd_table_entry* xrcd_table_search (struct ib_uverbs_device*,struct inode*) ; 

__attribute__((used)) static struct ib_xrcd *find_xrcd(struct ib_uverbs_device *dev, struct inode *inode)
{
	struct xrcd_table_entry *entry;

	entry = xrcd_table_search(dev, inode);
	if (!entry)
		return NULL;

	return entry->xrcd;
}