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
typedef  int u32 ;
struct mvpp2_port {int first_rxq; int /*<<< orphan*/  priv; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int MVPP2_CLS_OVERSIZE_RXQ_LOW_BITS ; 
 int MVPP2_CLS_OVERSIZE_RXQ_LOW_MASK ; 
 int /*<<< orphan*/  MVPP2_CLS_OVERSIZE_RXQ_LOW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_CLS_SWFWD_P2HQ_REG (int /*<<< orphan*/ ) ; 
 int MVPP2_CLS_SWFWD_PCTRL_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_CLS_SWFWD_PCTRL_REG ; 
 int mvpp2_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mvpp2_cls_oversize_rxq_set(struct mvpp2_port *port)
{
	u32 val;

	mvpp2_write(port->priv, MVPP2_CLS_OVERSIZE_RXQ_LOW_REG(port->id),
		    port->first_rxq & MVPP2_CLS_OVERSIZE_RXQ_LOW_MASK);

	mvpp2_write(port->priv, MVPP2_CLS_SWFWD_P2HQ_REG(port->id),
		    (port->first_rxq >> MVPP2_CLS_OVERSIZE_RXQ_LOW_BITS));

	val = mvpp2_read(port->priv, MVPP2_CLS_SWFWD_PCTRL_REG);
	val |= MVPP2_CLS_SWFWD_PCTRL_MASK(port->id);
	mvpp2_write(port->priv, MVPP2_CLS_SWFWD_PCTRL_REG, val);
}