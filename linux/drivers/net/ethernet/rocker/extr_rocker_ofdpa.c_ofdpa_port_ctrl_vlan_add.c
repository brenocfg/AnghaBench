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
struct ofdpa_port {scalar_t__* ctrls; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int OFDPA_CTRL_MAX ; 
 int /*<<< orphan*/ * ofdpa_ctrls ; 
 int ofdpa_port_ctrl_vlan (struct ofdpa_port*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_ctrl_vlan_add(struct ofdpa_port *ofdpa_port, int flags,
				    __be16 vlan_id)
{
	int err = 0;
	int i;

	for (i = 0; i < OFDPA_CTRL_MAX; i++) {
		if (ofdpa_port->ctrls[i]) {
			err = ofdpa_port_ctrl_vlan(ofdpa_port, flags,
						   &ofdpa_ctrls[i], vlan_id);
			if (err)
				return err;
		}
	}

	return err;
}