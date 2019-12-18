#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pucan_timing_slow {int ewl; int /*<<< orphan*/  sjw_t; int /*<<< orphan*/  tseg2; int /*<<< orphan*/  tseg1; int /*<<< orphan*/  brp; } ;
struct TYPE_2__ {int ctrlmode; } ;
struct peak_canfd_priv {int /*<<< orphan*/  ndev; TYPE_1__ can; } ;
struct can_bittiming {scalar_t__ brp; scalar_t__ phase_seg2; scalar_t__ phase_seg1; scalar_t__ prop_seg; scalar_t__ sjw; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  PUCAN_CMD_TIMING_SLOW ; 
 int /*<<< orphan*/  PUCAN_TSLOW_BRP (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TSLOW_SJW_T (scalar_t__,int) ; 
 int /*<<< orphan*/  PUCAN_TSLOW_TSEG1 (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TSLOW_TSEG2 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pucan_timing_slow* pucan_add_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pucan_init_cmd (struct peak_canfd_priv*) ; 
 int pucan_write_cmd (struct peak_canfd_priv*) ; 

__attribute__((used)) static int pucan_set_timing_slow(struct peak_canfd_priv *priv,
				 const struct can_bittiming *pbt)
{
	struct pucan_timing_slow *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_TIMING_SLOW);

	cmd->sjw_t = PUCAN_TSLOW_SJW_T(pbt->sjw - 1,
				priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES);
	cmd->tseg1 = PUCAN_TSLOW_TSEG1(pbt->prop_seg + pbt->phase_seg1 - 1);
	cmd->tseg2 = PUCAN_TSLOW_TSEG2(pbt->phase_seg2 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TSLOW_BRP(pbt->brp - 1));

	cmd->ewl = 96;	/* default */

	netdev_dbg(priv->ndev,
		   "nominal: brp=%u tseg1=%u tseg2=%u sjw=%u\n",
		   le16_to_cpu(cmd->brp), cmd->tseg1, cmd->tseg2, cmd->sjw_t);

	return pucan_write_cmd(priv);
}