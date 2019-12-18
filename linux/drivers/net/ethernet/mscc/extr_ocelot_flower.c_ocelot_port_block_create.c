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
struct ocelot_port_block {struct ocelot_port* port; } ;
struct ocelot_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ocelot_port_block* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocelot_port_block*
ocelot_port_block_create(struct ocelot_port *port)
{
	struct ocelot_port_block *port_block;

	port_block = kzalloc(sizeof(*port_block), GFP_KERNEL);
	if (!port_block)
		return NULL;

	port_block->port = port;

	return port_block;
}