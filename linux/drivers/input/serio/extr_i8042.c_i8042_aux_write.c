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
struct serio {struct i8042_port* port_data; } ;
struct i8042_port {int mux; } ;

/* Variables and functions */
 scalar_t__ I8042_CMD_AUX_SEND ; 
 scalar_t__ I8042_CMD_MUX_SEND ; 
 int i8042_command (unsigned char*,scalar_t__) ; 

__attribute__((used)) static int i8042_aux_write(struct serio *serio, unsigned char c)
{
	struct i8042_port *port = serio->port_data;

	return i8042_command(&c, port->mux == -1 ?
					I8042_CMD_AUX_SEND :
					I8042_CMD_MUX_SEND + port->mux);
}