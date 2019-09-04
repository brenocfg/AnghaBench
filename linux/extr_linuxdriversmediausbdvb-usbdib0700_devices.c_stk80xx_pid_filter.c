#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_adapter {TYPE_2__* fe_adap; struct dib0700_adapter_state* priv; } ;
struct TYPE_3__ {int (* pid_filter ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
struct dib0700_adapter_state {TYPE_1__ dib8000_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stk80xx_pid_filter(struct dvb_usb_adapter *adapter, int index,
	u16 pid, int onoff)
{
	struct dib0700_adapter_state *state = adapter->priv;

	return state->dib8000_ops.pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
}