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
struct rtsx_pcr {struct completion* finish_me; int /*<<< orphan*/  remove_pci; scalar_t__ done; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rtsx_pci_stop_cmd (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (struct completion*,int /*<<< orphan*/ ) ; 

void rtsx_pci_complete_unfinished_transfer(struct rtsx_pcr *pcr)
{
	struct completion finish;

	pcr->finish_me = &finish;
	init_completion(&finish);

	if (pcr->done)
		complete(pcr->done);

	if (!pcr->remove_pci)
		rtsx_pci_stop_cmd(pcr);

	wait_for_completion_interruptible_timeout(&finish,
			msecs_to_jiffies(2));
	pcr->finish_me = NULL;
}