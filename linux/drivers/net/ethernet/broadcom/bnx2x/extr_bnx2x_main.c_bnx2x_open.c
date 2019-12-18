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
struct net_device {int dummy; } ;
struct bnx2x {int stats_init; int /*<<< orphan*/  recovery_state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_RECOVERY_DONE ; 
 int /*<<< orphan*/  BNX2X_RECOVERY_FAILED ; 
 int BP_PATH (struct bnx2x*) ; 
 int EAGAIN ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  LOAD_OPEN ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ bnx2x_chk_parity_attn (struct bnx2x*,int*,int) ; 
 int bnx2x_get_load_status (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_leader_reset (struct bnx2x*) ; 
 int bnx2x_nic_load (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_reset_is_done (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_set_power_state (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_reset_global (struct bnx2x*) ; 
 scalar_t__ bnx2x_trylock_leader_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  udp_tunnel_get_rx_info (struct net_device*) ; 

__attribute__((used)) static int bnx2x_open(struct net_device *dev)
{
	struct bnx2x *bp = netdev_priv(dev);
	int rc;

	bp->stats_init = true;

	netif_carrier_off(dev);

	bnx2x_set_power_state(bp, PCI_D0);

	/* If parity had happen during the unload, then attentions
	 * and/or RECOVERY_IN_PROGRES may still be set. In this case we
	 * want the first function loaded on the current engine to
	 * complete the recovery.
	 * Parity recovery is only relevant for PF driver.
	 */
	if (IS_PF(bp)) {
		int other_engine = BP_PATH(bp) ? 0 : 1;
		bool other_load_status, load_status;
		bool global = false;

		other_load_status = bnx2x_get_load_status(bp, other_engine);
		load_status = bnx2x_get_load_status(bp, BP_PATH(bp));
		if (!bnx2x_reset_is_done(bp, BP_PATH(bp)) ||
		    bnx2x_chk_parity_attn(bp, &global, true)) {
			do {
				/* If there are attentions and they are in a
				 * global blocks, set the GLOBAL_RESET bit
				 * regardless whether it will be this function
				 * that will complete the recovery or not.
				 */
				if (global)
					bnx2x_set_reset_global(bp);

				/* Only the first function on the current
				 * engine should try to recover in open. In case
				 * of attentions in global blocks only the first
				 * in the chip should try to recover.
				 */
				if ((!load_status &&
				     (!global || !other_load_status)) &&
				      bnx2x_trylock_leader_lock(bp) &&
				      !bnx2x_leader_reset(bp)) {
					netdev_info(bp->dev,
						    "Recovered in open\n");
					break;
				}

				/* recovery has failed... */
				bnx2x_set_power_state(bp, PCI_D3hot);
				bp->recovery_state = BNX2X_RECOVERY_FAILED;

				BNX2X_ERR("Recovery flow hasn't been properly completed yet. Try again later.\n"
					  "If you still see this message after a few retries then power cycle is required.\n");

				return -EAGAIN;
			} while (0);
		}
	}

	bp->recovery_state = BNX2X_RECOVERY_DONE;
	rc = bnx2x_nic_load(bp, LOAD_OPEN);
	if (rc)
		return rc;

	if (IS_PF(bp))
		udp_tunnel_get_rx_info(dev);

	return 0;
}