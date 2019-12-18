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
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {scalar_t__ stp_state; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 int OFDPA_OP_FLAG_LEARNED ; 
 int OFDPA_OP_FLAG_NOWAIT ; 
 int ofdpa_port_fdb (struct ofdpa_port*,unsigned char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ofdpa_port_ev_mac_vlan_seen(struct rocker_port *rocker_port,
				       const unsigned char *addr,
				       __be16 vlan_id)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;
	int flags = OFDPA_OP_FLAG_NOWAIT | OFDPA_OP_FLAG_LEARNED;

	if (ofdpa_port->stp_state != BR_STATE_LEARNING &&
	    ofdpa_port->stp_state != BR_STATE_FORWARDING)
		return 0;

	return ofdpa_port_fdb(ofdpa_port, addr, vlan_id, flags);
}