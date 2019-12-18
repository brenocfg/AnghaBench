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
struct serio {struct olpc_apsp* port_data; } ;
struct olpc_apsp {scalar_t__ open_count; scalar_t__ base; } ;

/* Variables and functions */
 unsigned int INT_0 ; 
 scalar_t__ PJ_INTERRUPT_MASK ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void olpc_apsp_close(struct serio *port)
{
	struct olpc_apsp *priv = port->port_data;
	unsigned int tmp;

	if (--priv->open_count == 0) {
		/* Disable interrupt 0 */
		tmp = readl(priv->base + PJ_INTERRUPT_MASK);
		writel(tmp | INT_0, priv->base + PJ_INTERRUPT_MASK);
	}
}