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
typedef  void* u8 ;
struct bfi_diag_ledtest_req_s {int /*<<< orphan*/  freq; int /*<<< orphan*/  led; int /*<<< orphan*/  portid; void* color; void* cmd; int /*<<< orphan*/  mh; } ;
struct TYPE_4__ {scalar_t__ msg; } ;
struct TYPE_3__ {TYPE_2__ mbcmd; } ;
struct bfa_diag_s {TYPE_1__ ledtest; int /*<<< orphan*/  ioc; } ;
struct bfa_diag_ledtest_s {int freq; int /*<<< orphan*/  led; scalar_t__ color; scalar_t__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_DIAG_H2I_LEDTEST ; 
 int /*<<< orphan*/  BFI_MC_DIAG ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,int) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

__attribute__((used)) static void
diag_ledtest_send(struct bfa_diag_s *diag, struct bfa_diag_ledtest_s *ledtest)
{
	struct bfi_diag_ledtest_req_s  *msg;

	msg = (struct bfi_diag_ledtest_req_s *)diag->ledtest.mbcmd.msg;
	/* build host command */
	bfi_h2i_set(msg->mh, BFI_MC_DIAG, BFI_DIAG_H2I_LEDTEST,
			bfa_ioc_portid(diag->ioc));

	/*
	 * convert the freq from N blinks per 10 sec to
	 * crossbow ontime value. We do it here because division is need
	 */
	if (ledtest->freq)
		ledtest->freq = 500 / ledtest->freq;

	if (ledtest->freq == 0)
		ledtest->freq = 1;

	bfa_trc(diag, ledtest->freq);
	/* mcpy(&ledtest_req->req, ledtest, sizeof(bfa_diag_ledtest_t)); */
	msg->cmd = (u8) ledtest->cmd;
	msg->color = (u8) ledtest->color;
	msg->portid = bfa_ioc_portid(diag->ioc);
	msg->led = ledtest->led;
	msg->freq = cpu_to_be16(ledtest->freq);

	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->ledtest.mbcmd);
}