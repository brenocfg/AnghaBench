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
struct mv88e6xxx_chip {int dummy; } ;
typedef  enum mv88e6xxx_policy_mapping { ____Placeholder_mv88e6xxx_policy_mapping } mv88e6xxx_policy_mapping ;
typedef  enum mv88e6xxx_policy_action { ____Placeholder_mv88e6xxx_policy_action } mv88e6xxx_policy_action ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MV88E6XXX_POLICY_ACTION_DISCARD 139 
#define  MV88E6XXX_POLICY_ACTION_MIRROR 138 
#define  MV88E6XXX_POLICY_ACTION_NORMAL 137 
#define  MV88E6XXX_POLICY_ACTION_TRAP 136 
#define  MV88E6XXX_POLICY_MAPPING_DA 135 
#define  MV88E6XXX_POLICY_MAPPING_ETYPE 134 
#define  MV88E6XXX_POLICY_MAPPING_OPT82 133 
#define  MV88E6XXX_POLICY_MAPPING_PPPOE 132 
#define  MV88E6XXX_POLICY_MAPPING_SA 131 
#define  MV88E6XXX_POLICY_MAPPING_UDP 130 
#define  MV88E6XXX_POLICY_MAPPING_VBAS 129 
#define  MV88E6XXX_POLICY_MAPPING_VTU 128 
 int /*<<< orphan*/  MV88E6XXX_PORT_POLICY_CTL ; 
 int MV88E6XXX_PORT_POLICY_CTL_DA_MASK ; 
 int MV88E6XXX_PORT_POLICY_CTL_DISCARD ; 
 int MV88E6XXX_PORT_POLICY_CTL_ETYPE_MASK ; 
 int MV88E6XXX_PORT_POLICY_CTL_MIRROR ; 
 int MV88E6XXX_PORT_POLICY_CTL_NORMAL ; 
 int MV88E6XXX_PORT_POLICY_CTL_OPT82_MASK ; 
 int MV88E6XXX_PORT_POLICY_CTL_PPPOE_MASK ; 
 int MV88E6XXX_PORT_POLICY_CTL_SA_MASK ; 
 int MV88E6XXX_PORT_POLICY_CTL_TRAP ; 
 int MV88E6XXX_PORT_POLICY_CTL_UDP_MASK ; 
 int MV88E6XXX_PORT_POLICY_CTL_VBAS_MASK ; 
 int MV88E6XXX_PORT_POLICY_CTL_VTU_MASK ; 
 int __bf_shf (int) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6352_port_set_policy(struct mv88e6xxx_chip *chip, int port,
			      enum mv88e6xxx_policy_mapping mapping,
			      enum mv88e6xxx_policy_action action)
{
	u16 reg, mask, val;
	int shift;
	int err;

	switch (mapping) {
	case MV88E6XXX_POLICY_MAPPING_DA:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_DA_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_DA_MASK;
		break;
	case MV88E6XXX_POLICY_MAPPING_SA:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_SA_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_SA_MASK;
		break;
	case MV88E6XXX_POLICY_MAPPING_VTU:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_VTU_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_VTU_MASK;
		break;
	case MV88E6XXX_POLICY_MAPPING_ETYPE:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_ETYPE_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_ETYPE_MASK;
		break;
	case MV88E6XXX_POLICY_MAPPING_PPPOE:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_PPPOE_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_PPPOE_MASK;
		break;
	case MV88E6XXX_POLICY_MAPPING_VBAS:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_VBAS_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_VBAS_MASK;
		break;
	case MV88E6XXX_POLICY_MAPPING_OPT82:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_OPT82_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_OPT82_MASK;
		break;
	case MV88E6XXX_POLICY_MAPPING_UDP:
		shift = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_UDP_MASK);
		mask = MV88E6XXX_PORT_POLICY_CTL_UDP_MASK;
		break;
	default:
		return -EOPNOTSUPP;
	}

	switch (action) {
	case MV88E6XXX_POLICY_ACTION_NORMAL:
		val = MV88E6XXX_PORT_POLICY_CTL_NORMAL;
		break;
	case MV88E6XXX_POLICY_ACTION_MIRROR:
		val = MV88E6XXX_PORT_POLICY_CTL_MIRROR;
		break;
	case MV88E6XXX_POLICY_ACTION_TRAP:
		val = MV88E6XXX_PORT_POLICY_CTL_TRAP;
		break;
	case MV88E6XXX_POLICY_ACTION_DISCARD:
		val = MV88E6XXX_PORT_POLICY_CTL_DISCARD;
		break;
	default:
		return -EOPNOTSUPP;
	}

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_POLICY_CTL, &reg);
	if (err)
		return err;

	reg &= ~mask;
	reg |= (val << shift) & mask;

	return mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_POLICY_CTL, reg);
}