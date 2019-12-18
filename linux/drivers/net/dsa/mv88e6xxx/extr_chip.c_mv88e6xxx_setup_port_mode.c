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
struct mv88e6xxx_chip {TYPE_1__* info; int /*<<< orphan*/  ds; } ;
struct TYPE_2__ {scalar_t__ tag_protocol; } ;

/* Variables and functions */
 scalar_t__ DSA_TAG_PROTO_DSA ; 
 scalar_t__ DSA_TAG_PROTO_EDSA ; 
 int EINVAL ; 
 scalar_t__ dsa_is_dsa_port (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dsa_is_user_port (int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_set_port_mode_dsa (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_set_port_mode_edsa (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_set_port_mode_normal (struct mv88e6xxx_chip*,int) ; 

__attribute__((used)) static int mv88e6xxx_setup_port_mode(struct mv88e6xxx_chip *chip, int port)
{
	if (dsa_is_dsa_port(chip->ds, port))
		return mv88e6xxx_set_port_mode_dsa(chip, port);

	if (dsa_is_user_port(chip->ds, port))
		return mv88e6xxx_set_port_mode_normal(chip, port);

	/* Setup CPU port mode depending on its supported tag format */
	if (chip->info->tag_protocol == DSA_TAG_PROTO_DSA)
		return mv88e6xxx_set_port_mode_dsa(chip, port);

	if (chip->info->tag_protocol == DSA_TAG_PROTO_EDSA)
		return mv88e6xxx_set_port_mode_edsa(chip, port);

	return -EINVAL;
}