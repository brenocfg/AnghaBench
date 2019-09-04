#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cardstate {int /*<<< orphan*/  myid; TYPE_1__* iif; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ isdn_if ;
struct TYPE_5__ {int command; scalar_t__ arg; int /*<<< orphan*/  driver; } ;
typedef  TYPE_2__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void gigaset_i4l_cmd(struct cardstate *cs, int cmd)
{
	isdn_if *iif = cs->iif;
	isdn_ctrl command;

	command.driver = cs->myid;
	command.command = cmd;
	command.arg = 0;
	iif->statcallb(&command);
}