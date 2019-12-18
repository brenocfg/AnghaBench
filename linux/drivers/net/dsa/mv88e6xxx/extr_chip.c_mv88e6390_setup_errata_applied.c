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
typedef  int u16 ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_port_hidden_read (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool mv88e6390_setup_errata_applied(struct mv88e6xxx_chip *chip)
{
	int port;
	int err;
	u16 val;

	for (port = 0; port < mv88e6xxx_num_ports(chip); port++) {
		err = mv88e6xxx_port_hidden_read(chip, 0xf, port, 0, &val);
		if (err) {
			dev_err(chip->dev,
				"Error reading hidden register: %d\n", err);
			return false;
		}
		if (val != 0x01c0)
			return false;
	}

	return true;
}