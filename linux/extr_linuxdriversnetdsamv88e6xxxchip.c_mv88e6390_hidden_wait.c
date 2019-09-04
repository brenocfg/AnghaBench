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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_RESERVED_1A ; 
 int /*<<< orphan*/  PORT_RESERVED_1A_BUSY ; 
 int /*<<< orphan*/  PORT_RESERVED_1A_CTRL_PORT ; 
 int mv88e6xxx_wait (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6390_hidden_wait(struct mv88e6xxx_chip *chip)
{
	return mv88e6xxx_wait(chip, PORT_RESERVED_1A_CTRL_PORT,
			      PORT_RESERVED_1A, PORT_RESERVED_1A_BUSY);
}