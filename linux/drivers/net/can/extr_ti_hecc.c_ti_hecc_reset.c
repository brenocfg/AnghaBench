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
struct ti_hecc_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HECC_CANES ; 
 int /*<<< orphan*/  HECC_CANES_CCE ; 
 int /*<<< orphan*/  HECC_CANGIF0 ; 
 int /*<<< orphan*/  HECC_CANGIF1 ; 
 int /*<<< orphan*/  HECC_CANMC ; 
 int /*<<< orphan*/  HECC_CANMC_CCR ; 
 int /*<<< orphan*/  HECC_CANMC_SCM ; 
 int /*<<< orphan*/  HECC_CANMC_SRES ; 
 int /*<<< orphan*/  HECC_CANMD ; 
 int /*<<< orphan*/  HECC_CANME ; 
 int /*<<< orphan*/  HECC_CANRIOC ; 
 int /*<<< orphan*/  HECC_CANRIOC_EN ; 
 int /*<<< orphan*/  HECC_CANRMP ; 
 int /*<<< orphan*/  HECC_CANTA ; 
 int /*<<< orphan*/  HECC_CANTIOC ; 
 int /*<<< orphan*/  HECC_CANTIOC_EN ; 
 scalar_t__ HECC_CCE_WAIT_COUNT ; 
 int /*<<< orphan*/  HECC_SET_REG ; 
 scalar_t__ hecc_get_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hecc_set_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ti_hecc_set_btc (struct ti_hecc_priv*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ti_hecc_reset(struct net_device *ndev)
{
	u32 cnt;
	struct ti_hecc_priv *priv = netdev_priv(ndev);

	netdev_dbg(ndev, "resetting hecc ...\n");
	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_SRES);

	/* Set change control request and wait till enabled */
	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_CCR);

	/* INFO: It has been observed that at times CCE bit may not be
	 * set and hw seems to be ok even if this bit is not set so
	 * timing out with a timing of 1ms to respect the specs
	 */
	cnt = HECC_CCE_WAIT_COUNT;
	while (!hecc_get_bit(priv, HECC_CANES, HECC_CANES_CCE) && cnt != 0) {
		--cnt;
		udelay(10);
	}

	/* Note: On HECC, BTC can be programmed only in initialization mode, so
	 * it is expected that the can bittiming parameters are set via ip
	 * utility before the device is opened
	 */
	ti_hecc_set_btc(priv);

	/* Clear CCR (and CANMC register) and wait for CCE = 0 enable */
	hecc_write(priv, HECC_CANMC, 0);

	/* INFO: CAN net stack handles bus off and hence disabling auto-bus-on
	 * hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_ABO);
	 */

	/* INFO: It has been observed that at times CCE bit may not be
	 * set and hw seems to be ok even if this bit is not set so
	 */
	cnt = HECC_CCE_WAIT_COUNT;
	while (hecc_get_bit(priv, HECC_CANES, HECC_CANES_CCE) && cnt != 0) {
		--cnt;
		udelay(10);
	}

	/* Enable TX and RX I/O Control pins */
	hecc_write(priv, HECC_CANTIOC, HECC_CANTIOC_EN);
	hecc_write(priv, HECC_CANRIOC, HECC_CANRIOC_EN);

	/* Clear registers for clean operation */
	hecc_write(priv, HECC_CANTA, HECC_SET_REG);
	hecc_write(priv, HECC_CANRMP, HECC_SET_REG);
	hecc_write(priv, HECC_CANGIF0, HECC_SET_REG);
	hecc_write(priv, HECC_CANGIF1, HECC_SET_REG);
	hecc_write(priv, HECC_CANME, 0);
	hecc_write(priv, HECC_CANMD, 0);

	/* SCC compat mode NOT supported (and not needed too) */
	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_SCM);
}