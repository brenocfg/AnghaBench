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
struct sdma_txreq {scalar_t__ sn; int /*<<< orphan*/  (* complete ) (struct sdma_txreq*,int) ;struct iowait* wait; } ;
struct sdma_engine {scalar_t__ head_sn; int /*<<< orphan*/  dd; } ;
struct iowait {int dummy; } ;
typedef  int /*<<< orphan*/  (* callback_t ) (struct sdma_txreq*,int) ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __sdma_txclean (int /*<<< orphan*/ ,struct sdma_txreq*) ; 
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iowait_drain_wakeup (struct iowait*) ; 
 scalar_t__ iowait_sdma_dec (struct iowait*) ; 
 int /*<<< orphan*/  stub1 (struct sdma_txreq*,int) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_out_sn (struct sdma_engine*,scalar_t__) ; 

__attribute__((used)) static inline void complete_tx(struct sdma_engine *sde,
			       struct sdma_txreq *tx,
			       int res)
{
	/* protect against complete modifying */
	struct iowait *wait = tx->wait;
	callback_t complete = tx->complete;

#ifdef CONFIG_HFI1_DEBUG_SDMA_ORDER
	trace_hfi1_sdma_out_sn(sde, tx->sn);
	if (WARN_ON_ONCE(sde->head_sn != tx->sn))
		dd_dev_err(sde->dd, "expected %llu got %llu\n",
			   sde->head_sn, tx->sn);
	sde->head_sn++;
#endif
	__sdma_txclean(sde->dd, tx);
	if (complete)
		(*complete)(tx, res);
	if (iowait_sdma_dec(wait))
		iowait_drain_wakeup(wait);
}