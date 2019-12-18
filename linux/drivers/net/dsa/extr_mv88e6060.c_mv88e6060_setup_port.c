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
struct mv88e6060_priv {int /*<<< orphan*/  ds; } ;
struct TYPE_4__ {TYPE_1__* cpu_dp; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  PORT_ASSOC_VECTOR ; 
 int /*<<< orphan*/  PORT_CONTROL ; 
 int PORT_CONTROL_INGRESS_MODE ; 
 int PORT_CONTROL_STATE_FORWARDING ; 
 int PORT_CONTROL_TRAILER ; 
 int /*<<< orphan*/  PORT_VLAN_MAP ; 
 int PORT_VLAN_MAP_DBNUM_SHIFT ; 
 int REG_PORT (int) ; 
 scalar_t__ dsa_is_cpu_port (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* dsa_to_port (int /*<<< orphan*/ ,int) ; 
 int dsa_user_ports (int /*<<< orphan*/ ) ; 
 int reg_write (struct mv88e6060_priv*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6060_setup_port(struct mv88e6060_priv *priv, int p)
{
	int addr = REG_PORT(p);
	int ret;

	/* Do not force flow control, disable Ingress and Egress
	 * Header tagging, disable VLAN tunneling, and set the port
	 * state to Forwarding.  Additionally, if this is the CPU
	 * port, enable Ingress and Egress Trailer tagging mode.
	 */
	ret = reg_write(priv, addr, PORT_CONTROL,
			dsa_is_cpu_port(priv->ds, p) ?
			PORT_CONTROL_TRAILER |
			PORT_CONTROL_INGRESS_MODE |
			PORT_CONTROL_STATE_FORWARDING :
			PORT_CONTROL_STATE_FORWARDING);
	if (ret)
		return ret;

	/* Port based VLAN map: give each port its own address
	 * database, allow the CPU port to talk to each of the 'real'
	 * ports, and allow each of the 'real' ports to only talk to
	 * the CPU port.
	 */
	ret = reg_write(priv, addr, PORT_VLAN_MAP,
			((p & 0xf) << PORT_VLAN_MAP_DBNUM_SHIFT) |
			(dsa_is_cpu_port(priv->ds, p) ?
			 dsa_user_ports(priv->ds) :
			 BIT(dsa_to_port(priv->ds, p)->cpu_dp->index)));
	if (ret)
		return ret;

	/* Port Association Vector: when learning source addresses
	 * of packets, add the address to the address database using
	 * a port bitmap that has only the bit for this port set and
	 * the other bits clear.
	 */
	return reg_write(priv, addr, PORT_ASSOC_VECTOR, BIT(p));
}