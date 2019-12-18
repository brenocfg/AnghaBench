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
struct slgt_info {int signals; int /*<<< orphan*/  reg_addr; } ;

/* Variables and functions */
 int IRQ_ALL ; 
 int IRQ_MASTER ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 int /*<<< orphan*/  rx_stop (struct slgt_info*) ; 
 int /*<<< orphan*/  set_signals (struct slgt_info*) ; 
 int /*<<< orphan*/  slgt_irq_off (struct slgt_info*,int) ; 
 int /*<<< orphan*/  tx_stop (struct slgt_info*) ; 

__attribute__((used)) static void reset_port(struct slgt_info *info)
{
	if (!info->reg_addr)
		return;

	tx_stop(info);
	rx_stop(info);

	info->signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
	set_signals(info);

	slgt_irq_off(info, IRQ_ALL | IRQ_MASTER);
}