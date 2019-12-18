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
struct c4iw_ep_common {int /*<<< orphan*/  history; TYPE_1__* cm_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rem_ref ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ID_DEREFED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void deref_cm_id(struct c4iw_ep_common *epc)
{
	epc->cm_id->rem_ref(epc->cm_id);
	epc->cm_id = NULL;
	set_bit(CM_ID_DEREFED, &epc->history);
}