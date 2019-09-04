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
struct pvr2_ioread {struct pvr2_ioread* sync_key_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_STRUCT ; 
 int /*<<< orphan*/  kfree (struct pvr2_ioread*) ; 
 int /*<<< orphan*/  pvr2_ioread_done (struct pvr2_ioread*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_ioread*) ; 

void pvr2_ioread_destroy(struct pvr2_ioread *cp)
{
	if (!cp) return;
	pvr2_ioread_done(cp);
	pvr2_trace(PVR2_TRACE_STRUCT,"pvr2_ioread_destroy id=%p",cp);
	if (cp->sync_key_ptr) {
		kfree(cp->sync_key_ptr);
		cp->sync_key_ptr = NULL;
	}
	kfree(cp);
}