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
struct TYPE_2__ {int flags; } ;
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int) ;TYPE_1__ devtype; } ;
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_RX ; 
 int XCAN_FLAG_RX_FIFO_MULTI ; 
 int XCAN_FSR_IRI_MASK ; 
 int /*<<< orphan*/  XCAN_FSR_OFFSET ; 
 int /*<<< orphan*/  XCAN_ICR_OFFSET ; 
 int /*<<< orphan*/  XCAN_IER_OFFSET ; 
 int XCAN_IXR_RXNEMP_MASK ; 
 int XCAN_IXR_RXOK_MASK ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xcan_rx (struct net_device*,int) ; 
 int xcan_rx_fifo_get_next_frame (struct xcan_priv*) ; 
 int xcan_rx_int_mask (struct xcan_priv*) ; 
 int /*<<< orphan*/  xcan_update_error_state_after_rxtx (struct net_device*) ; 
 scalar_t__ xcanfd_rx (struct net_device*,int) ; 

__attribute__((used)) static int xcan_rx_poll(struct napi_struct *napi, int quota)
{
	struct net_device *ndev = napi->dev;
	struct xcan_priv *priv = netdev_priv(ndev);
	u32 ier;
	int work_done = 0;
	int frame_offset;

	while ((frame_offset = xcan_rx_fifo_get_next_frame(priv)) >= 0 &&
	       (work_done < quota)) {
		if (xcan_rx_int_mask(priv) & XCAN_IXR_RXOK_MASK)
			work_done += xcanfd_rx(ndev, frame_offset);
		else
			work_done += xcan_rx(ndev, frame_offset);

		if (priv->devtype.flags & XCAN_FLAG_RX_FIFO_MULTI)
			/* increment read index */
			priv->write_reg(priv, XCAN_FSR_OFFSET,
					XCAN_FSR_IRI_MASK);
		else
			/* clear rx-not-empty (will actually clear only if
			 * empty)
			 */
			priv->write_reg(priv, XCAN_ICR_OFFSET,
					XCAN_IXR_RXNEMP_MASK);
	}

	if (work_done) {
		can_led_event(ndev, CAN_LED_EVENT_RX);
		xcan_update_error_state_after_rxtx(ndev);
	}

	if (work_done < quota) {
		napi_complete_done(napi, work_done);
		ier = priv->read_reg(priv, XCAN_IER_OFFSET);
		ier |= xcan_rx_int_mask(priv);
		priv->write_reg(priv, XCAN_IER_OFFSET, ier);
	}
	return work_done;
}