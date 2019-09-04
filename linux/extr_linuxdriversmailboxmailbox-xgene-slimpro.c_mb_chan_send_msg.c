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
typedef  int /*<<< orphan*/  u32 ;
struct slimpro_mbox_chan {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ REG_DB_DOUT0 ; 
 scalar_t__ REG_DB_DOUT1 ; 
 scalar_t__ REG_DB_OUT ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mb_chan_send_msg(struct slimpro_mbox_chan *mb_chan, u32 *msg)
{
	writel(msg[1], mb_chan->reg + REG_DB_DOUT0);
	writel(msg[2], mb_chan->reg + REG_DB_DOUT1);
	writel(msg[0], mb_chan->reg + REG_DB_OUT);
}