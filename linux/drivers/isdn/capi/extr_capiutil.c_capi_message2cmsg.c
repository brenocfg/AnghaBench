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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int l; int ApplId; int Messagenumber; int /*<<< orphan*/ * m; int /*<<< orphan*/  par; int /*<<< orphan*/  Subcommand; int /*<<< orphan*/  Command; scalar_t__ p; } ;
typedef  TYPE_1__ _cmsg ;

/* Variables and functions */
 int /*<<< orphan*/  byteTRcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capi_cmd2par (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  message_2_pars (TYPE_1__*) ; 
 int /*<<< orphan*/  wordTRcpy (int /*<<< orphan*/ *,int*) ; 

unsigned capi_message2cmsg(_cmsg *cmsg, u8 *msg)
{
	memset(cmsg, 0, sizeof(_cmsg));
	cmsg->m = msg;
	cmsg->l = 8;
	cmsg->p = 0;
	byteTRcpy(cmsg->m + 4, &cmsg->Command);
	byteTRcpy(cmsg->m + 5, &cmsg->Subcommand);
	cmsg->par = capi_cmd2par(cmsg->Command, cmsg->Subcommand);
	if (!cmsg->par)
		return 1;	/* invalid command/subcommand */

	message_2_pars(cmsg);

	wordTRcpy(msg + 0, &cmsg->l);
	wordTRcpy(cmsg->m + 2, &cmsg->ApplId);
	wordTRcpy(cmsg->m + 6, &cmsg->Messagenumber);

	return 0;
}