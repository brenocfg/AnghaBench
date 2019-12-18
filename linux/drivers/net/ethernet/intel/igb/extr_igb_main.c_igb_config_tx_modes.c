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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct igb_ring {int idleslope; int hicredit; int /*<<< orphan*/  locredit; int /*<<< orphan*/  sendslope; scalar_t__ launchtime_enable; scalar_t__ cbs_enable; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; struct net_device* netdev; struct igb_ring** tx_ring; } ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (unsigned long long,int) ; 
 int /*<<< orphan*/  E1000_I210_TQAVCC (int) ; 
 int /*<<< orphan*/  E1000_I210_TQAVCTRL ; 
 int /*<<< orphan*/  E1000_I210_TQAVHC (int) ; 
 int E1000_TQAVCC_IDLESLOPE_MASK ; 
 int E1000_TQAVCTRL_DATATRANARB ; 
 int E1000_TQAVCTRL_DATATRANTIM ; 
 int E1000_TQAVCTRL_FETCHTIME_DELTA ; 
 int ETH_FRAME_LEN ; 
 int /*<<< orphan*/  QUEUE_MODE_STREAM_RESERVATION ; 
 int /*<<< orphan*/  QUEUE_MODE_STRICT_PRIORITY ; 
 int /*<<< orphan*/  TX_QUEUE_PRIO_HIGH ; 
 int /*<<< orphan*/  TX_QUEUE_PRIO_LOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  is_any_cbs_enabled (struct igb_adapter*) ; 
 int /*<<< orphan*/  is_any_txtime_enabled (struct igb_adapter*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,char*,char*,int,unsigned long long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_queue_mode (struct e1000_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tx_desc_fetch_prio (struct e1000_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_config_tx_modes(struct igb_adapter *adapter, int queue)
{
	struct igb_ring *ring = adapter->tx_ring[queue];
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	u32 tqavcc, tqavctrl;
	u16 value;

	WARN_ON(hw->mac.type != e1000_i210);
	WARN_ON(queue < 0 || queue > 1);

	/* If any of the Qav features is enabled, configure queues as SR and
	 * with HIGH PRIO. If none is, then configure them with LOW PRIO and
	 * as SP.
	 */
	if (ring->cbs_enable || ring->launchtime_enable) {
		set_tx_desc_fetch_prio(hw, queue, TX_QUEUE_PRIO_HIGH);
		set_queue_mode(hw, queue, QUEUE_MODE_STREAM_RESERVATION);
	} else {
		set_tx_desc_fetch_prio(hw, queue, TX_QUEUE_PRIO_LOW);
		set_queue_mode(hw, queue, QUEUE_MODE_STRICT_PRIORITY);
	}

	/* If CBS is enabled, set DataTranARB and config its parameters. */
	if (ring->cbs_enable || queue == 0) {
		/* i210 does not allow the queue 0 to be in the Strict
		 * Priority mode while the Qav mode is enabled, so,
		 * instead of disabling strict priority mode, we give
		 * queue 0 the maximum of credits possible.
		 *
		 * See section 8.12.19 of the i210 datasheet, "Note:
		 * Queue0 QueueMode must be set to 1b when
		 * TransmitMode is set to Qav."
		 */
		if (queue == 0 && !ring->cbs_enable) {
			/* max "linkspeed" idleslope in kbps */
			ring->idleslope = 1000000;
			ring->hicredit = ETH_FRAME_LEN;
		}

		/* Always set data transfer arbitration to credit-based
		 * shaper algorithm on TQAVCTRL if CBS is enabled for any of
		 * the queues.
		 */
		tqavctrl = rd32(E1000_I210_TQAVCTRL);
		tqavctrl |= E1000_TQAVCTRL_DATATRANARB;
		wr32(E1000_I210_TQAVCTRL, tqavctrl);

		/* According to i210 datasheet section 7.2.7.7, we should set
		 * the 'idleSlope' field from TQAVCC register following the
		 * equation:
		 *
		 * For 100 Mbps link speed:
		 *
		 *     value = BW * 0x7735 * 0.2                          (E1)
		 *
		 * For 1000Mbps link speed:
		 *
		 *     value = BW * 0x7735 * 2                            (E2)
		 *
		 * E1 and E2 can be merged into one equation as shown below.
		 * Note that 'link-speed' is in Mbps.
		 *
		 *     value = BW * 0x7735 * 2 * link-speed
		 *                           --------------               (E3)
		 *                                1000
		 *
		 * 'BW' is the percentage bandwidth out of full link speed
		 * which can be found with the following equation. Note that
		 * idleSlope here is the parameter from this function which
		 * is in kbps.
		 *
		 *     BW =     idleSlope
		 *          -----------------                             (E4)
		 *          link-speed * 1000
		 *
		 * That said, we can come up with a generic equation to
		 * calculate the value we should set it TQAVCC register by
		 * replacing 'BW' in E3 by E4. The resulting equation is:
		 *
		 * value =     idleSlope     * 0x7735 * 2 * link-speed
		 *         -----------------            --------------    (E5)
		 *         link-speed * 1000                 1000
		 *
		 * 'link-speed' is present in both sides of the fraction so
		 * it is canceled out. The final equation is the following:
		 *
		 *     value = idleSlope * 61034
		 *             -----------------                          (E6)
		 *                  1000000
		 *
		 * NOTE: For i210, given the above, we can see that idleslope
		 *       is represented in 16.38431 kbps units by the value at
		 *       the TQAVCC register (1Gbps / 61034), which reduces
		 *       the granularity for idleslope increments.
		 *       For instance, if you want to configure a 2576kbps
		 *       idleslope, the value to be written on the register
		 *       would have to be 157.23. If rounded down, you end
		 *       up with less bandwidth available than originally
		 *       required (~2572 kbps). If rounded up, you end up
		 *       with a higher bandwidth (~2589 kbps). Below the
		 *       approach we take is to always round up the
		 *       calculated value, so the resulting bandwidth might
		 *       be slightly higher for some configurations.
		 */
		value = DIV_ROUND_UP_ULL(ring->idleslope * 61034ULL, 1000000);

		tqavcc = rd32(E1000_I210_TQAVCC(queue));
		tqavcc &= ~E1000_TQAVCC_IDLESLOPE_MASK;
		tqavcc |= value;
		wr32(E1000_I210_TQAVCC(queue), tqavcc);

		wr32(E1000_I210_TQAVHC(queue),
		     0x80000000 + ring->hicredit * 0x7735);
	} else {

		/* Set idleSlope to zero. */
		tqavcc = rd32(E1000_I210_TQAVCC(queue));
		tqavcc &= ~E1000_TQAVCC_IDLESLOPE_MASK;
		wr32(E1000_I210_TQAVCC(queue), tqavcc);

		/* Set hiCredit to zero. */
		wr32(E1000_I210_TQAVHC(queue), 0);

		/* If CBS is not enabled for any queues anymore, then return to
		 * the default state of Data Transmission Arbitration on
		 * TQAVCTRL.
		 */
		if (!is_any_cbs_enabled(adapter)) {
			tqavctrl = rd32(E1000_I210_TQAVCTRL);
			tqavctrl &= ~E1000_TQAVCTRL_DATATRANARB;
			wr32(E1000_I210_TQAVCTRL, tqavctrl);
		}
	}

	/* If LaunchTime is enabled, set DataTranTIM. */
	if (ring->launchtime_enable) {
		/* Always set DataTranTIM on TQAVCTRL if LaunchTime is enabled
		 * for any of the SR queues, and configure fetchtime delta.
		 * XXX NOTE:
		 *     - LaunchTime will be enabled for all SR queues.
		 *     - A fixed offset can be added relative to the launch
		 *       time of all packets if configured at reg LAUNCH_OS0.
		 *       We are keeping it as 0 for now (default value).
		 */
		tqavctrl = rd32(E1000_I210_TQAVCTRL);
		tqavctrl |= E1000_TQAVCTRL_DATATRANTIM |
		       E1000_TQAVCTRL_FETCHTIME_DELTA;
		wr32(E1000_I210_TQAVCTRL, tqavctrl);
	} else {
		/* If Launchtime is not enabled for any SR queues anymore,
		 * then clear DataTranTIM on TQAVCTRL and clear fetchtime delta,
		 * effectively disabling Launchtime.
		 */
		if (!is_any_txtime_enabled(adapter)) {
			tqavctrl = rd32(E1000_I210_TQAVCTRL);
			tqavctrl &= ~E1000_TQAVCTRL_DATATRANTIM;
			tqavctrl &= ~E1000_TQAVCTRL_FETCHTIME_DELTA;
			wr32(E1000_I210_TQAVCTRL, tqavctrl);
		}
	}

	/* XXX: In i210 controller the sendSlope and loCredit parameters from
	 * CBS are not configurable by software so we don't do any 'controller
	 * configuration' in respect to these parameters.
	 */

	netdev_dbg(netdev, "Qav Tx mode: cbs %s, launchtime %s, queue %d idleslope %d sendslope %d hiCredit %d locredit %d\n",
		   ring->cbs_enable ? "enabled" : "disabled",
		   ring->launchtime_enable ? "enabled" : "disabled",
		   queue,
		   ring->idleslope, ring->sendslope,
		   ring->hicredit, ring->locredit);
}