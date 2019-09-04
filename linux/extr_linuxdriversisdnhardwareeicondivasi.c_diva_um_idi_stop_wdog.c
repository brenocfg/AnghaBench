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
struct TYPE_2__ {int /*<<< orphan*/  diva_timer_id; } ;
typedef  TYPE_1__ diva_um_idi_os_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ diva_um_id_get_os_context (void*) ; 

void diva_um_idi_stop_wdog(void *entity)
{
	diva_um_idi_os_context_t *p_os;

	if (entity &&
	    ((p_os =
	      (diva_um_idi_os_context_t *)
	      diva_um_id_get_os_context(entity)))) {
		del_timer(&p_os->diva_timer_id);
	}
}