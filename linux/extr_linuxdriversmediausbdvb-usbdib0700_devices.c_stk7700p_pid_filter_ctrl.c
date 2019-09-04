#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_3__* fe_adap; struct dib0700_adapter_state* priv; TYPE_1__* dev; } ;
struct dib0700_state {scalar_t__ is_dib7000pc; } ;
struct TYPE_5__ {int (* pid_filter_ctrl ) (int /*<<< orphan*/ ,int) ;} ;
struct dib0700_adapter_state {TYPE_2__ dib7000p_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  fe; } ;
struct TYPE_4__ {struct dib0700_state* priv; } ;

/* Variables and functions */
 int dib7000m_pid_filter_ctrl (int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stk7700p_pid_filter_ctrl(struct dvb_usb_adapter *adapter, int onoff)
{
	struct dib0700_state *st = adapter->dev->priv;
	struct dib0700_adapter_state *state = adapter->priv;
	if (st->is_dib7000pc)
		return state->dib7000p_ops.pid_filter_ctrl(adapter->fe_adap[0].fe, onoff);
	return dib7000m_pid_filter_ctrl(adapter->fe_adap[0].fe, onoff);
}