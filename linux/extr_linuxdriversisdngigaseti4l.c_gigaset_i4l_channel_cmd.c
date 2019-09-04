#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bc_state {int /*<<< orphan*/  channel; TYPE_1__* cs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* statcallb ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ isdn_if ;
struct TYPE_7__ {int command; int /*<<< orphan*/  arg; int /*<<< orphan*/  driver; } ;
typedef  TYPE_3__ isdn_ctrl ;
struct TYPE_5__ {int /*<<< orphan*/  myid; TYPE_2__* iif; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void gigaset_i4l_channel_cmd(struct bc_state *bcs, int cmd)
{
	isdn_if *iif = bcs->cs->iif;
	isdn_ctrl command;

	command.driver = bcs->cs->myid;
	command.command = cmd;
	command.arg = bcs->channel;
	iif->statcallb(&command);
}