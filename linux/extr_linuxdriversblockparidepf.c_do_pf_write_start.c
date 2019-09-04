#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_WRITE_10 ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 scalar_t__ PF_MAX_RETRIES ; 
 int /*<<< orphan*/  PF_TMO ; 
 int /*<<< orphan*/  STAT_BUSY ; 
 int STAT_DRQ ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  do_pf_write_done ; 
 int /*<<< orphan*/  next_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nice ; 
 int /*<<< orphan*/  pf_block ; 
 int /*<<< orphan*/  pf_buf ; 
 int pf_busy ; 
 TYPE_1__* pf_current ; 
 scalar_t__ pf_mask ; 
 scalar_t__ pf_next_buf () ; 
 int /*<<< orphan*/  pf_ready ; 
 scalar_t__ pf_retries ; 
 int /*<<< orphan*/  pf_run ; 
 scalar_t__ pf_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pf_wait (TYPE_1__*,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  pi_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_do_claimed (int /*<<< orphan*/ ,void (*) ()) ; 
 int /*<<< orphan*/  pi_write_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ps_set_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_pf_write_start(void)
{
	pf_busy = 1;

	if (pf_start(pf_current, ATAPI_WRITE_10, pf_block, pf_run)) {
		pi_disconnect(pf_current->pi);
		if (pf_retries < PF_MAX_RETRIES) {
			pf_retries++;
			pi_do_claimed(pf_current->pi, do_pf_write_start);
			return;
		}
		next_request(BLK_STS_IOERR);
		return;
	}

	while (1) {
		if (pf_wait(pf_current, STAT_BUSY, STAT_DRQ | STAT_ERR,
			    "write block", "data wait") & STAT_ERR) {
			pi_disconnect(pf_current->pi);
			if (pf_retries < PF_MAX_RETRIES) {
				pf_retries++;
				pi_do_claimed(pf_current->pi, do_pf_write_start);
				return;
			}
			next_request(BLK_STS_IOERR);
			return;
		}
		pi_write_block(pf_current->pi, pf_buf, 512);
		if (pf_next_buf())
			break;
	}
	pf_mask = 0;
	ps_set_intr(do_pf_write_done, pf_ready, PF_TMO, nice);
}