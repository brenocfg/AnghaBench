#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct fman {TYPE_1__* intr_mng; } ;
typedef  enum fman_intr_type { ____Placeholder_fman_intr_type } fman_intr_type ;
typedef  enum fman_event_modules { ____Placeholder_fman_event_modules } fman_event_modules ;
struct TYPE_2__ {int /*<<< orphan*/ * src_handle; int /*<<< orphan*/ * isr_cb; } ;

/* Variables and functions */
 int FMAN_EV_CNT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int get_module_event (int,int /*<<< orphan*/ ,int) ; 

void fman_unregister_intr(struct fman *fman, enum fman_event_modules module,
			  u8 mod_id, enum fman_intr_type intr_type)
{
	int event = 0;

	event = get_module_event(module, mod_id, intr_type);
	WARN_ON(event >= FMAN_EV_CNT);

	fman->intr_mng[event].isr_cb = NULL;
	fman->intr_mng[event].src_handle = NULL;
}