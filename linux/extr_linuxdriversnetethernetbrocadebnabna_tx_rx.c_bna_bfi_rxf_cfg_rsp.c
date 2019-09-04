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
struct bna_rxf {int dummy; } ;
struct bfi_msgq_mhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXF_E_FW_RESP ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rxf*,int /*<<< orphan*/ ) ; 

void
bna_bfi_rxf_cfg_rsp(struct bna_rxf *rxf, struct bfi_msgq_mhdr *msghdr)
{
	bfa_fsm_send_event(rxf, RXF_E_FW_RESP);
}