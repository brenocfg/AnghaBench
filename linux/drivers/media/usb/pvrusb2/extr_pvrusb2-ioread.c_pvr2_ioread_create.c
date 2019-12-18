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
struct pvr2_ioread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PVR2_TRACE_STRUCT ; 
 int /*<<< orphan*/  kfree (struct pvr2_ioread*) ; 
 struct pvr2_ioread* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pvr2_ioread_init (struct pvr2_ioread*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_ioread*) ; 

struct pvr2_ioread *pvr2_ioread_create(void)
{
	struct pvr2_ioread *cp;
	cp = kzalloc(sizeof(*cp),GFP_KERNEL);
	if (!cp) return NULL;
	pvr2_trace(PVR2_TRACE_STRUCT,"pvr2_ioread_create id=%p",cp);
	if (pvr2_ioread_init(cp) < 0) {
		kfree(cp);
		return NULL;
	}
	return cp;
}