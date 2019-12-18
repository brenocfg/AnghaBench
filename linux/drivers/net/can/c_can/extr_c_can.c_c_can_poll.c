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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct c_can_priv {int last_status; int (* read_reg ) (struct c_can_priv*,int /*<<< orphan*/ ) ;scalar_t__ type; TYPE_1__ can; int /*<<< orphan*/  (* write_reg ) (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sie_pending; } ;

/* Variables and functions */
 scalar_t__ BOSCH_D_CAN ; 
 scalar_t__ CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  C_CAN_BUS_OFF ; 
 int /*<<< orphan*/  C_CAN_ERROR_PASSIVE ; 
 int /*<<< orphan*/  C_CAN_ERROR_WARNING ; 
 int /*<<< orphan*/  C_CAN_NO_ERROR ; 
 int /*<<< orphan*/  C_CAN_STS_REG ; 
 int LEC_MASK ; 
 int /*<<< orphan*/  LEC_UNUSED ; 
 int STATUS_BOFF ; 
 int STATUS_EPASS ; 
 int STATUS_EWARN ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_can_do_rx_poll (struct net_device*,int) ; 
 int /*<<< orphan*/  c_can_do_tx (struct net_device*) ; 
 scalar_t__ c_can_handle_bus_err (struct net_device*,int) ; 
 scalar_t__ c_can_handle_state_change (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_can_irq_control (struct c_can_priv*,int) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct c_can_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct c_can_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c_can_poll(struct napi_struct *napi, int quota)
{
	struct net_device *dev = napi->dev;
	struct c_can_priv *priv = netdev_priv(dev);
	u16 curr, last = priv->last_status;
	int work_done = 0;

	/* Only read the status register if a status interrupt was pending */
	if (atomic_xchg(&priv->sie_pending, 0)) {
		priv->last_status = curr = priv->read_reg(priv, C_CAN_STS_REG);
		/* Ack status on C_CAN. D_CAN is self clearing */
		if (priv->type != BOSCH_D_CAN)
			priv->write_reg(priv, C_CAN_STS_REG, LEC_UNUSED);
	} else {
		/* no change detected ... */
		curr = last;
	}

	/* handle state changes */
	if ((curr & STATUS_EWARN) && (!(last & STATUS_EWARN))) {
		netdev_dbg(dev, "entered error warning state\n");
		work_done += c_can_handle_state_change(dev, C_CAN_ERROR_WARNING);
	}

	if ((curr & STATUS_EPASS) && (!(last & STATUS_EPASS))) {
		netdev_dbg(dev, "entered error passive state\n");
		work_done += c_can_handle_state_change(dev, C_CAN_ERROR_PASSIVE);
	}

	if ((curr & STATUS_BOFF) && (!(last & STATUS_BOFF))) {
		netdev_dbg(dev, "entered bus off state\n");
		work_done += c_can_handle_state_change(dev, C_CAN_BUS_OFF);
		goto end;
	}

	/* handle bus recovery events */
	if ((!(curr & STATUS_BOFF)) && (last & STATUS_BOFF)) {
		netdev_dbg(dev, "left bus off state\n");
		work_done += c_can_handle_state_change(dev, C_CAN_ERROR_PASSIVE);
	}

	if ((!(curr & STATUS_EPASS)) && (last & STATUS_EPASS)) {
		netdev_dbg(dev, "left error passive state\n");
		work_done += c_can_handle_state_change(dev, C_CAN_ERROR_WARNING);
	}

	if ((!(curr & STATUS_EWARN)) && (last & STATUS_EWARN)) {
		netdev_dbg(dev, "left error warning state\n");
		work_done += c_can_handle_state_change(dev, C_CAN_NO_ERROR);
	}

	/* handle lec errors on the bus */
	work_done += c_can_handle_bus_err(dev, curr & LEC_MASK);

	/* Handle Tx/Rx events. We do this unconditionally */
	work_done += c_can_do_rx_poll(dev, (quota - work_done));
	c_can_do_tx(dev);

end:
	if (work_done < quota) {
		napi_complete_done(napi, work_done);
		/* enable all IRQs if we are not in bus off state */
		if (priv->can.state != CAN_STATE_BUS_OFF)
			c_can_irq_control(priv, true);
	}

	return work_done;
}