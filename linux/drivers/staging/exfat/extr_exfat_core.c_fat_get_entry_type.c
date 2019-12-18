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
typedef  int /*<<< orphan*/  u32 ;
struct dos_dentry_t {int* name; int attr; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int ATTR_EXTEND ; 
 int ATTR_SUBDIR ; 
 int ATTR_VOLUME ; 
 int /*<<< orphan*/  TYPE_DELETED ; 
 int /*<<< orphan*/  TYPE_DIR ; 
 int /*<<< orphan*/  TYPE_EXTEND ; 
 int /*<<< orphan*/  TYPE_FILE ; 
 int /*<<< orphan*/  TYPE_UNUSED ; 
 int /*<<< orphan*/  TYPE_VOLUME ; 

u32 fat_get_entry_type(struct dentry_t *p_entry)
{
	struct dos_dentry_t *ep = (struct dos_dentry_t *)p_entry;

	if (*(ep->name) == 0x0)
		return TYPE_UNUSED;

	else if (*(ep->name) == 0xE5)
		return TYPE_DELETED;

	else if (ep->attr == ATTR_EXTEND)
		return TYPE_EXTEND;

	else if ((ep->attr & (ATTR_SUBDIR | ATTR_VOLUME)) == ATTR_VOLUME)
		return TYPE_VOLUME;

	else if ((ep->attr & (ATTR_SUBDIR | ATTR_VOLUME)) == ATTR_SUBDIR)
		return TYPE_DIR;

	return TYPE_FILE;
}