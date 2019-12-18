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
struct slimpro_mbox_chan {scalar_t__ reg; void** rx_msg; } ;

/* Variables and functions */
 scalar_t__ REG_DB_DIN0 ; 
 scalar_t__ REG_DB_DIN1 ; 
 scalar_t__ REG_DB_IN ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static void mb_chan_recv_msg(struct slimpro_mbox_chan *mb_chan)
{
	mb_chan->rx_msg[1] = readl(mb_chan->reg + REG_DB_DIN0);
	mb_chan->rx_msg[2] = readl(mb_chan->reg + REG_DB_DIN1);
	mb_chan->rx_msg[0] = readl(mb_chan->reg + REG_DB_IN);
}