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
typedef  int /*<<< orphan*/  u16 ;
struct pucan_tx_abort {int /*<<< orphan*/  flags; } ;
struct peak_canfd_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUCAN_CMD_TX_ABORT ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct pucan_tx_abort* pucan_add_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pucan_init_cmd (struct peak_canfd_priv*) ; 
 int pucan_write_cmd (struct peak_canfd_priv*) ; 

__attribute__((used)) static int pucan_tx_abort(struct peak_canfd_priv *priv, u16 flags)
{
	struct pucan_tx_abort *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_TX_ABORT);

	cmd->flags = cpu_to_le16(flags);

	return pucan_write_cmd(priv);
}