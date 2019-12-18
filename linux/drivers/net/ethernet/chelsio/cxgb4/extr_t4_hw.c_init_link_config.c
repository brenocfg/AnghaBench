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
struct link_config {int pcaps; int requested_fc; int fc; int acaps; scalar_t__ speed_caps; int /*<<< orphan*/  autoneg; void* def_acaps; int /*<<< orphan*/  fec; int /*<<< orphan*/  requested_fec; scalar_t__ speed; scalar_t__ lpacaps; } ;
typedef  void* fw_port_cap32_t ;

/* Variables and functions */
 int ADVERT_MASK ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  FEC_AUTO ; 
 int FW_PORT_CAP32_ANEG ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int /*<<< orphan*/  fwcap_to_cc_fec (void*) ; 
 scalar_t__ fwcap_to_fwspeed (void*) ; 

__attribute__((used)) static void init_link_config(struct link_config *lc, fw_port_cap32_t pcaps,
			     fw_port_cap32_t acaps)
{
	lc->pcaps = pcaps;
	lc->def_acaps = acaps;
	lc->lpacaps = 0;
	lc->speed_caps = 0;
	lc->speed = 0;
	lc->requested_fc = lc->fc = PAUSE_RX | PAUSE_TX;

	/* For Forward Error Control, we default to whatever the Firmware
	 * tells us the Link is currently advertising.
	 */
	lc->requested_fec = FEC_AUTO;
	lc->fec = fwcap_to_cc_fec(lc->def_acaps);

	/* If the Port is capable of Auto-Negtotiation, initialize it as
	 * "enabled" and copy over all of the Physical Port Capabilities
	 * to the Advertised Port Capabilities.  Otherwise mark it as
	 * Auto-Negotiate disabled and select the highest supported speed
	 * for the link.  Note parallel structure in t4_link_l1cfg_core()
	 * and t4_handle_get_port_info().
	 */
	if (lc->pcaps & FW_PORT_CAP32_ANEG) {
		lc->acaps = lc->pcaps & ADVERT_MASK;
		lc->autoneg = AUTONEG_ENABLE;
		lc->requested_fc |= PAUSE_AUTONEG;
	} else {
		lc->acaps = 0;
		lc->autoneg = AUTONEG_DISABLE;
		lc->speed_caps = fwcap_to_fwspeed(acaps);
	}
}