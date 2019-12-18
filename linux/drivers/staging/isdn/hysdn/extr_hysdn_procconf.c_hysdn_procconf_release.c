#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__ procconf; int /*<<< orphan*/  myid; } ;
typedef  TYPE_1__ hysdn_card ;
struct TYPE_6__ {int /*<<< orphan*/  proc_net; } ;

/* Variables and functions */
 char* PROC_CONF_BASENAME ; 
 unsigned char* PROC_SUBDIR_NAME ; 
 TYPE_1__* card_root ; 
 int /*<<< orphan*/  hysdn_proc_entry ; 
 int /*<<< orphan*/  hysdn_proclog_release (TYPE_1__*) ; 
 TYPE_2__ init_net ; 
 int /*<<< orphan*/  remove_proc_entry (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (unsigned char*,char*,char*,int /*<<< orphan*/ ) ; 

void
hysdn_procconf_release(void)
{
	hysdn_card *card;
	unsigned char conf_name[20];

	card = card_root;	/* start with first card */
	while (card) {

		sprintf(conf_name, "%s%d", PROC_CONF_BASENAME, card->myid);
		if (card->procconf)
			remove_proc_entry(conf_name, hysdn_proc_entry);

		hysdn_proclog_release(card);	/* init the log file entry */

		card = card->next;	/* point to next card */
	}

	remove_proc_entry(PROC_SUBDIR_NAME, init_net.proc_net);
}