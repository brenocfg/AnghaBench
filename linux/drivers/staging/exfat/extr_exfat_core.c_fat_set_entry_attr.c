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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct dos_dentry_t {scalar_t__ attr; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */

void fat_set_entry_attr(struct dentry_t *p_entry, u32 attr)
{
	struct dos_dentry_t *ep = (struct dos_dentry_t *)p_entry;

	ep->attr = (u8)attr;
}