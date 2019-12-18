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
typedef  scalar_t__ u32 ;
struct file_dentry_t {int type; int /*<<< orphan*/  attr; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int ATTR_ARCHIVE ; 
 int ATTR_SUBDIR ; 
 int ATTR_SYMLINK ; 
 int /*<<< orphan*/  SET16_A (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TYPE_BITMAP ; 
 scalar_t__ TYPE_DELETED ; 
 scalar_t__ TYPE_DIR ; 
 scalar_t__ TYPE_EXTEND ; 
 scalar_t__ TYPE_FILE ; 
 scalar_t__ TYPE_STREAM ; 
 scalar_t__ TYPE_SYMLINK ; 
 scalar_t__ TYPE_UNUSED ; 
 scalar_t__ TYPE_UPCASE ; 
 scalar_t__ TYPE_VOLUME ; 

void exfat_set_entry_type(struct dentry_t *p_entry, u32 type)
{
	struct file_dentry_t *ep = (struct file_dentry_t *)p_entry;

	if (type == TYPE_UNUSED) {
		ep->type = 0x0;
	} else if (type == TYPE_DELETED) {
		ep->type &= ~0x80;
	} else if (type == TYPE_STREAM) {
		ep->type = 0xC0;
	} else if (type == TYPE_EXTEND) {
		ep->type = 0xC1;
	} else if (type == TYPE_BITMAP) {
		ep->type = 0x81;
	} else if (type == TYPE_UPCASE) {
		ep->type = 0x82;
	} else if (type == TYPE_VOLUME) {
		ep->type = 0x83;
	} else if (type == TYPE_DIR) {
		ep->type = 0x85;
		SET16_A(ep->attr, ATTR_SUBDIR);
	} else if (type == TYPE_FILE) {
		ep->type = 0x85;
		SET16_A(ep->attr, ATTR_ARCHIVE);
	} else if (type == TYPE_SYMLINK) {
		ep->type = 0x85;
		SET16_A(ep->attr, ATTR_ARCHIVE | ATTR_SYMLINK);
	}
}