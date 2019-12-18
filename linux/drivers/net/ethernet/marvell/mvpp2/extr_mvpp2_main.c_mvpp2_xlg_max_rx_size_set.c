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
struct mvpp2_port {int pkt_size; scalar_t__ base; } ;

/* Variables and functions */
 int MVPP22_XLG_CTRL1_FRAMESIZELIMIT_MASK ; 
 int MVPP22_XLG_CTRL1_FRAMESIZELIMIT_OFFS ; 
 scalar_t__ MVPP22_XLG_CTRL1_REG ; 
 int MVPP2_MH_SIZE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void mvpp2_xlg_max_rx_size_set(struct mvpp2_port *port)
{
	u32 val;

	val =  readl(port->base + MVPP22_XLG_CTRL1_REG);
	val &= ~MVPP22_XLG_CTRL1_FRAMESIZELIMIT_MASK;
	val |= ((port->pkt_size - MVPP2_MH_SIZE) / 2) <<
	       MVPP22_XLG_CTRL1_FRAMESIZELIMIT_OFFS;
	writel(val, port->base + MVPP22_XLG_CTRL1_REG);
}