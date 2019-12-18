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
struct bnx2x_fp_txdata {scalar_t__ tx_pkt_prod; scalar_t__ tx_pkt_cons; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 

__attribute__((used)) static inline int bnx2x_has_tx_work_unload(struct bnx2x_fp_txdata *txdata)
{
	/* Tell compiler that consumer and producer can change */
	barrier();
	return txdata->tx_pkt_prod != txdata->tx_pkt_cons;
}