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
struct mvpp2_port {int /*<<< orphan*/  priv; int /*<<< orphan*/  id; } ;
struct mvpp2_cls_c2_entry {int /*<<< orphan*/ * tcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_PORT_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_c2_read (int /*<<< orphan*/ ,int,struct mvpp2_cls_c2_entry*) ; 
 int /*<<< orphan*/  mvpp2_cls_c2_write (int /*<<< orphan*/ ,struct mvpp2_cls_c2_entry*) ; 

__attribute__((used)) static void mvpp22_port_c2_lookup_disable(struct mvpp2_port *port, int entry)
{
	struct mvpp2_cls_c2_entry c2;

	mvpp2_cls_c2_read(port->priv, entry, &c2);

	/* Clear the port map so that the entry doesn't match anymore */
	c2.tcam[4] &= ~(MVPP22_CLS_C2_PORT_ID(BIT(port->id)));

	mvpp2_cls_c2_write(port->priv, &c2);
}