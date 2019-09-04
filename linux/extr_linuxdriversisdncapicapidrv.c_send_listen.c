#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cipmask2; int /*<<< orphan*/  cipmask; int /*<<< orphan*/  contrnr; int /*<<< orphan*/  msgid; } ;
typedef  TYPE_2__ capidrv_contr ;
struct TYPE_7__ {int /*<<< orphan*/  applid; } ;
struct TYPE_9__ {TYPE_1__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_LISTEN_REQ ; 
 int /*<<< orphan*/  capi_fill_LISTEN_REQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdcmsg ; 
 TYPE_6__ global ; 
 int /*<<< orphan*/  listen_change_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_message (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_listen(capidrv_contr *card)
{
	capi_fill_LISTEN_REQ(&cmdcmsg, global.ap.applid,
			     card->msgid++,
			     card->contrnr, /* controller */
			     1 << 6,	/* Infomask */
			     card->cipmask,
			     card->cipmask2,
			     NULL, NULL);
	listen_change_state(card, EV_LISTEN_REQ);
	send_message(card, &cmdcmsg);
}