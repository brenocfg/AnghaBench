#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct boot_data {int dummy; } ;
struct TYPE_5__ {scalar_t__ state; int debug_flags; int /*<<< orphan*/  (* set_errlog_state ) (TYPE_1__*,int) ;struct boot_data* boot; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 scalar_t__ CARD_STATE_RUN ; 
 int EFAULT ; 
 int LOG_POF_OPEN ; 
 int /*<<< orphan*/  hysdn_addlog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kfree (struct boot_data*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

int
pof_write_close(hysdn_card *card)
{
	struct boot_data *boot = card->boot;	/* pointer to boot specific data */

	if (!boot)
		return (-EFAULT);	/* invalid call */

	card->boot = NULL;	/* no boot active */
	kfree(boot);

	if (card->state == CARD_STATE_RUN)
		card->set_errlog_state(card, 1);	/* activate error log */

	if (card->debug_flags & LOG_POF_OPEN)
		hysdn_addlog(card, "POF close: success");

	return (0);
}