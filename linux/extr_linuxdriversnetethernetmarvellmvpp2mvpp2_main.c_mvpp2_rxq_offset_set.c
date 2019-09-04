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
struct mvpp2_port {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_RXQ_CONFIG_REG (int) ; 
 int MVPP2_RXQ_PACKET_OFFSET_MASK ; 
 int MVPP2_RXQ_PACKET_OFFSET_OFFS ; 
 int mvpp2_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvpp2_rxq_offset_set(struct mvpp2_port *port,
				 int prxq, int offset)
{
	u32 val;

	/* Convert offset from bytes to units of 32 bytes */
	offset = offset >> 5;

	val = mvpp2_read(port->priv, MVPP2_RXQ_CONFIG_REG(prxq));
	val &= ~MVPP2_RXQ_PACKET_OFFSET_MASK;

	/* Offset is in */
	val |= ((offset << MVPP2_RXQ_PACKET_OFFSET_OFFS) &
		    MVPP2_RXQ_PACKET_OFFSET_MASK);

	mvpp2_write(port->priv, MVPP2_RXQ_CONFIG_REG(prxq), val);
}