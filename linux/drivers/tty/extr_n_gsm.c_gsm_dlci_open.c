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
struct gsm_dlci {TYPE_1__* gsm; int /*<<< orphan*/  addr; int /*<<< orphan*/  state; int /*<<< orphan*/  t1; } ;
struct TYPE_2__ {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLCI_OPEN ; 
 int debug ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gsm_dlci_open(struct gsm_dlci *dlci)
{
	/* Note that SABM UA .. SABM UA first UA lost can mean that we go
	   open -> open */
	del_timer(&dlci->t1);
	/* This will let a tty open continue */
	dlci->state = DLCI_OPEN;
	if (debug & 8)
		pr_debug("DLCI %d goes open.\n", dlci->addr);
	wake_up(&dlci->gsm->event);
}