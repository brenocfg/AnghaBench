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
struct bnx2x_fp_txdata {int /*<<< orphan*/  tx_pkt_cons; int /*<<< orphan*/  tx_pkt_prod; int /*<<< orphan*/  txq_index; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 scalar_t__ bnx2x_has_tx_work_unload (struct bnx2x_fp_txdata*) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline int bnx2x_clean_tx_queue(struct bnx2x *bp,
				       struct bnx2x_fp_txdata *txdata)
{
	int cnt = 1000;

	while (bnx2x_has_tx_work_unload(txdata)) {
		if (!cnt) {
			BNX2X_ERR("timeout waiting for queue[%d]: txdata->tx_pkt_prod(%d) != txdata->tx_pkt_cons(%d)\n",
				  txdata->txq_index, txdata->tx_pkt_prod,
				  txdata->tx_pkt_cons);
#ifdef BNX2X_STOP_ON_ERROR
			bnx2x_panic();
			return -EBUSY;
#else
			break;
#endif
		}
		cnt--;
		usleep_range(1000, 2000);
	}

	return 0;
}