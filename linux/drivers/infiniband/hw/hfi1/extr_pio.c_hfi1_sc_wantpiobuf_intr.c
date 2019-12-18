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
typedef  scalar_t__ u32 ;
struct send_context {int /*<<< orphan*/  credit_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  sc_add_credit_return_intr (struct send_context*) ; 
 int /*<<< orphan*/  sc_del_credit_return_intr (struct send_context*) ; 
 int /*<<< orphan*/  sc_return_credits (struct send_context*) ; 
 int /*<<< orphan*/  trace_hfi1_wantpiointr (struct send_context*,scalar_t__,int /*<<< orphan*/ ) ; 

void hfi1_sc_wantpiobuf_intr(struct send_context *sc, u32 needint)
{
	if (needint)
		sc_add_credit_return_intr(sc);
	else
		sc_del_credit_return_intr(sc);
	trace_hfi1_wantpiointr(sc, needint, sc->credit_ctrl);
	if (needint)
		sc_return_credits(sc);
}