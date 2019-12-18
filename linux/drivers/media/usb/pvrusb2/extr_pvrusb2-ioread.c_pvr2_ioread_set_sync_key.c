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
struct pvr2_ioread {unsigned int sync_key_len; int /*<<< orphan*/ * sync_key_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,unsigned int) ; 

void pvr2_ioread_set_sync_key(struct pvr2_ioread *cp,
			      const char *sync_key_ptr,
			      unsigned int sync_key_len)
{
	if (!cp) return;

	if (!sync_key_ptr) sync_key_len = 0;
	if ((sync_key_len == cp->sync_key_len) &&
	    ((!sync_key_len) ||
	     (!memcmp(sync_key_ptr,cp->sync_key_ptr,sync_key_len)))) return;

	if (sync_key_len != cp->sync_key_len) {
		if (cp->sync_key_ptr) {
			kfree(cp->sync_key_ptr);
			cp->sync_key_ptr = NULL;
		}
		cp->sync_key_len = 0;
		if (sync_key_len) {
			cp->sync_key_ptr = kmalloc(sync_key_len,GFP_KERNEL);
			if (cp->sync_key_ptr) {
				cp->sync_key_len = sync_key_len;
			}
		}
	}
	if (!cp->sync_key_len) return;
	memcpy(cp->sync_key_ptr,sync_key_ptr,cp->sync_key_len);
}