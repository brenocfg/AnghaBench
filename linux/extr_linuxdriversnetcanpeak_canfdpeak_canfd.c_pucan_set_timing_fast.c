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
struct pucan_timing_fast {int /*<<< orphan*/  sjw; int /*<<< orphan*/  tseg2; int /*<<< orphan*/  tseg1; int /*<<< orphan*/  brp; } ;
struct peak_canfd_priv {int /*<<< orphan*/  ndev; } ;
struct can_bittiming {scalar_t__ brp; scalar_t__ phase_seg2; scalar_t__ phase_seg1; scalar_t__ prop_seg; scalar_t__ sjw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUCAN_CMD_TIMING_FAST ; 
 int /*<<< orphan*/  PUCAN_TFAST_BRP (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TFAST_SJW (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TFAST_TSEG1 (scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_TFAST_TSEG2 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pucan_timing_fast* pucan_add_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pucan_init_cmd (struct peak_canfd_priv*) ; 
 int pucan_write_cmd (struct peak_canfd_priv*) ; 

__attribute__((used)) static int pucan_set_timing_fast(struct peak_canfd_priv *priv,
				 const struct can_bittiming *pbt)
{
	struct pucan_timing_fast *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_TIMING_FAST);

	cmd->sjw = PUCAN_TFAST_SJW(pbt->sjw - 1);
	cmd->tseg1 = PUCAN_TFAST_TSEG1(pbt->prop_seg + pbt->phase_seg1 - 1);
	cmd->tseg2 = PUCAN_TFAST_TSEG2(pbt->phase_seg2 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TFAST_BRP(pbt->brp - 1));

	netdev_dbg(priv->ndev,
		   "data: brp=%u tseg1=%u tseg2=%u sjw=%u\n",
		   le16_to_cpu(cmd->brp), cmd->tseg1, cmd->tseg2, cmd->sjw);

	return pucan_write_cmd(priv);
}