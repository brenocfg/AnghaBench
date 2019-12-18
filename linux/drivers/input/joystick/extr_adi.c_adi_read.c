#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct adi_port {TYPE_1__* adi; } ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int adi_decode (TYPE_1__*) ; 
 int /*<<< orphan*/  adi_move_bits (struct adi_port*,scalar_t__) ; 
 int /*<<< orphan*/  adi_read_packet (struct adi_port*) ; 

__attribute__((used)) static int adi_read(struct adi_port *port)
{
	int i;
	int result = 0;

	adi_read_packet(port);
	adi_move_bits(port, port->adi[0].length);

	for (i = 0; i < 2; i++)
		if (port->adi[i].length)
			 result |= adi_decode(port->adi + i);

	return result;
}