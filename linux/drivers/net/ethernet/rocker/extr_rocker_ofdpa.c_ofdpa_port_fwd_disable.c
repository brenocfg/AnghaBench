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
struct ofdpa_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_DISABLED ; 
 scalar_t__ ofdpa_port_is_bridged (struct ofdpa_port*) ; 
 int ofdpa_port_stp_update (struct ofdpa_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_fwd_disable(struct ofdpa_port *ofdpa_port, int flags)
{
	if (ofdpa_port_is_bridged(ofdpa_port))
		/* bridge STP will disable port */
		return 0;

	/* port is not bridged, so simulate going to DISABLED state */
	return ofdpa_port_stp_update(ofdpa_port, flags,
				     BR_STATE_DISABLED);
}