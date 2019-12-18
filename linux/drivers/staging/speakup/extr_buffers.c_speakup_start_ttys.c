#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tty_stopped; } ;
struct TYPE_7__ {TYPE_2__* d; } ;
struct TYPE_5__ {scalar_t__ tty; } ;
struct TYPE_6__ {TYPE_1__ port; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 TYPE_4__** speakup_console ; 
 int /*<<< orphan*/  start_tty (scalar_t__) ; 
 TYPE_3__* vc_cons ; 

void speakup_start_ttys(void)
{
	int i;

	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		if (speakup_console[i] && speakup_console[i]->tty_stopped)
			continue;
		if (vc_cons[i].d && vc_cons[i].d->port.tty)
			start_tty(vc_cons[i].d->port.tty);
	}
}