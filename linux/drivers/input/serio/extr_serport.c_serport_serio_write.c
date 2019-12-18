#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct serport {TYPE_2__* tty; } ;
struct serio {struct serport* port_data; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* write ) (TYPE_2__*,unsigned char*,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,unsigned char*,int) ; 

__attribute__((used)) static int serport_serio_write(struct serio *serio, unsigned char data)
{
	struct serport *serport = serio->port_data;
	return -(serport->tty->ops->write(serport->tty, &data, 1) != 1);
}