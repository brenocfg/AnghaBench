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
struct timer_list {int dummy; } ;
struct cardstate {int /*<<< orphan*/  dev; } ;
struct bas_cardstate {struct cardstate* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_ATREADY ; 
 int /*<<< orphan*/  BS_ATTIMER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct bas_cardstate* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_cbsend (struct cardstate*) ; 
 int /*<<< orphan*/  timer_atrdy ; 
 struct bas_cardstate* ucs ; 
 int /*<<< orphan*/  update_basstate (struct bas_cardstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atrdy_timeout(struct timer_list *t)
{
	struct bas_cardstate *ucs = from_timer(ucs, t, timer_atrdy);
	struct cardstate *cs = ucs->cs;

	dev_warn(cs->dev, "timeout waiting for HD_READY_SEND_ATDATA\n");

	/* fake the missing signal - what else can I do? */
	update_basstate(ucs, BS_ATREADY, BS_ATTIMER);
	start_cbsend(cs);
}