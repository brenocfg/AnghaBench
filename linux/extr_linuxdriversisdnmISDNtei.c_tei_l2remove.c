#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* ctrl ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  list; } ;
struct layer2 {TYPE_2__ ch; int /*<<< orphan*/  tei; TYPE_1__* tm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_CHANNEL ; 
 int /*<<< orphan*/  ID_REMOVE ; 
 int /*<<< orphan*/  MDL_REMOVE_REQ ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_tei_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tei_l2 (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tei_l2remove(struct layer2 *l2)
{
	put_tei_msg(l2->tm->mgr, ID_REMOVE, 0, l2->tei);
	tei_l2(l2, MDL_REMOVE_REQ, 0);
	list_del(&l2->ch.list);
	l2->ch.ctrl(&l2->ch, CLOSE_CHANNEL, NULL);
}