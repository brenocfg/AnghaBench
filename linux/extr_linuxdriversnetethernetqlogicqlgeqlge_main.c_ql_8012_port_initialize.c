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
typedef  int u32 ;
struct ql_adapter {int port_init; int /*<<< orphan*/  xg_sem_mask; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_CFG ; 
 int GLOBAL_CFG_JUMBO ; 
 int GLOBAL_CFG_RESET ; 
 int GLOBAL_CFG_RX_STAT_EN ; 
 int GLOBAL_CFG_TX_STAT_EN ; 
 int /*<<< orphan*/  MAC_RX_PARAMS ; 
 int /*<<< orphan*/  MAC_TX_PARAMS ; 
 int MAC_TX_PARAMS_JUMBO ; 
 int /*<<< orphan*/  RX_CFG ; 
 int RX_CFG_EN ; 
 int RX_CFG_RESET ; 
 int /*<<< orphan*/  STS ; 
 int /*<<< orphan*/  TX_CFG ; 
 int TX_CFG_EN ; 
 int TX_CFG_RESET ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_crit (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_info (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_read_xgmac_reg (struct ql_adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ql_sem_trylock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_wait_reg_rdy (struct ql_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 
 int ql_write_xgmac_reg (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_8012_port_initialize(struct ql_adapter *qdev)
{
	int status = 0;
	u32 data;

	if (ql_sem_trylock(qdev, qdev->xg_sem_mask)) {
		/* Another function has the semaphore, so
		 * wait for the port init bit to come ready.
		 */
		netif_info(qdev, link, qdev->ndev,
			   "Another function has the semaphore, so wait for the port init bit to come ready.\n");
		status = ql_wait_reg_rdy(qdev, STS, qdev->port_init, 0);
		if (status) {
			netif_crit(qdev, link, qdev->ndev,
				   "Port initialize timed out.\n");
		}
		return status;
	}

	netif_info(qdev, link, qdev->ndev, "Got xgmac semaphore!.\n");
	/* Set the core reset. */
	status = ql_read_xgmac_reg(qdev, GLOBAL_CFG, &data);
	if (status)
		goto end;
	data |= GLOBAL_CFG_RESET;
	status = ql_write_xgmac_reg(qdev, GLOBAL_CFG, data);
	if (status)
		goto end;

	/* Clear the core reset and turn on jumbo for receiver. */
	data &= ~GLOBAL_CFG_RESET;	/* Clear core reset. */
	data |= GLOBAL_CFG_JUMBO;	/* Turn on jumbo. */
	data |= GLOBAL_CFG_TX_STAT_EN;
	data |= GLOBAL_CFG_RX_STAT_EN;
	status = ql_write_xgmac_reg(qdev, GLOBAL_CFG, data);
	if (status)
		goto end;

	/* Enable transmitter, and clear it's reset. */
	status = ql_read_xgmac_reg(qdev, TX_CFG, &data);
	if (status)
		goto end;
	data &= ~TX_CFG_RESET;	/* Clear the TX MAC reset. */
	data |= TX_CFG_EN;	/* Enable the transmitter. */
	status = ql_write_xgmac_reg(qdev, TX_CFG, data);
	if (status)
		goto end;

	/* Enable receiver and clear it's reset. */
	status = ql_read_xgmac_reg(qdev, RX_CFG, &data);
	if (status)
		goto end;
	data &= ~RX_CFG_RESET;	/* Clear the RX MAC reset. */
	data |= RX_CFG_EN;	/* Enable the receiver. */
	status = ql_write_xgmac_reg(qdev, RX_CFG, data);
	if (status)
		goto end;

	/* Turn on jumbo. */
	status =
	    ql_write_xgmac_reg(qdev, MAC_TX_PARAMS, MAC_TX_PARAMS_JUMBO | (0x2580 << 16));
	if (status)
		goto end;
	status =
	    ql_write_xgmac_reg(qdev, MAC_RX_PARAMS, 0x2580);
	if (status)
		goto end;

	/* Signal to the world that the port is enabled.        */
	ql_write32(qdev, STS, ((qdev->port_init << 16) | qdev->port_init));
end:
	ql_sem_unlock(qdev, qdev->xg_sem_mask);
	return status;
}