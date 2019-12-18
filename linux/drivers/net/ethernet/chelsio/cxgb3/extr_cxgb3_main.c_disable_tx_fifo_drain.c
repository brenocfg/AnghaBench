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
struct TYPE_2__ {scalar_t__ offset; } ;
struct port_info {TYPE_1__ mac; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ A_XGM_TXFIFO_CFG ; 
 int /*<<< orphan*/  F_ENDROPPKT ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_tx_fifo_drain(struct adapter *adapter,
				  struct port_info *pi)
{
	t3_set_reg_field(adapter, A_XGM_TXFIFO_CFG + pi->mac.offset,
			 F_ENDROPPKT, 0);
}