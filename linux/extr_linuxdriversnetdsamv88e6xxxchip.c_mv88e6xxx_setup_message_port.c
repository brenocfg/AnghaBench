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
struct mv88e6xxx_chip {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int dsa_is_dsa_port (int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_port_set_message_port (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static int mv88e6xxx_setup_message_port(struct mv88e6xxx_chip *chip, int port)
{
	bool message = dsa_is_dsa_port(chip->ds, port);

	return mv88e6xxx_port_set_message_port(chip, port, message);
}