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
struct file_dentry_t {int type; int /*<<< orphan*/  attr; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int ATTR_SUBDIR ; 
 int GET16_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ACL ; 
 int /*<<< orphan*/  TYPE_ACLTAB ; 
 int /*<<< orphan*/  TYPE_BENIGN_PRI ; 
 int /*<<< orphan*/  TYPE_BENIGN_SEC ; 
 int /*<<< orphan*/  TYPE_BITMAP ; 
 int /*<<< orphan*/  TYPE_CRITICAL_PRI ; 
 int /*<<< orphan*/  TYPE_CRITICAL_SEC ; 
 int /*<<< orphan*/  TYPE_DELETED ; 
 int /*<<< orphan*/  TYPE_DIR ; 
 int /*<<< orphan*/  TYPE_EXTEND ; 
 int /*<<< orphan*/  TYPE_FILE ; 
 int /*<<< orphan*/  TYPE_GUID ; 
 int /*<<< orphan*/  TYPE_INVALID ; 
 int /*<<< orphan*/  TYPE_PADDING ; 
 int /*<<< orphan*/  TYPE_STREAM ; 
 int /*<<< orphan*/  TYPE_UNUSED ; 
 int /*<<< orphan*/  TYPE_UPCASE ; 
 int /*<<< orphan*/  TYPE_VOLUME ; 

u32 exfat_get_entry_type(struct dentry_t *p_entry)
{
	struct file_dentry_t *ep = (struct file_dentry_t *)p_entry;

	if (ep->type == 0x0) {
		return TYPE_UNUSED;
	} else if (ep->type < 0x80) {
		return TYPE_DELETED;
	} else if (ep->type == 0x80) {
		return TYPE_INVALID;
	} else if (ep->type < 0xA0) {
		if (ep->type == 0x81) {
			return TYPE_BITMAP;
		} else if (ep->type == 0x82) {
			return TYPE_UPCASE;
		} else if (ep->type == 0x83) {
			return TYPE_VOLUME;
		} else if (ep->type == 0x85) {
			if (GET16_A(ep->attr) & ATTR_SUBDIR)
				return TYPE_DIR;
			else
				return TYPE_FILE;
		}
		return TYPE_CRITICAL_PRI;
	} else if (ep->type < 0xC0) {
		if (ep->type == 0xA0)
			return TYPE_GUID;
		else if (ep->type == 0xA1)
			return TYPE_PADDING;
		else if (ep->type == 0xA2)
			return TYPE_ACLTAB;
		return TYPE_BENIGN_PRI;
	} else if (ep->type < 0xE0) {
		if (ep->type == 0xC0)
			return TYPE_STREAM;
		else if (ep->type == 0xC1)
			return TYPE_EXTEND;
		else if (ep->type == 0xC2)
			return TYPE_ACL;
		return TYPE_CRITICAL_SEC;
	}

	return TYPE_BENIGN_SEC;
}