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
struct c4iw_ep_common {TYPE_1__* cm_id; int /*<<< orphan*/  history; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* add_ref ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ID_REFED ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void ref_cm_id(struct c4iw_ep_common *epc)
{
	set_bit(CM_ID_REFED, &epc->history);
	epc->cm_id->add_ref(epc->cm_id);
}