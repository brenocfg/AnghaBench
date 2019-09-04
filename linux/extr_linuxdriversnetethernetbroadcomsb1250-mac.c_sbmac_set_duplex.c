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
typedef  int uint64_t ;
struct sbmac_softc {int sbm_duplex; int sbm_fc; scalar_t__ sbm_state; int /*<<< orphan*/  sbm_maccfg; } ;
typedef  enum sbmac_fc { ____Placeholder_sbmac_fc } sbmac_fc ;
typedef  enum sbmac_duplex { ____Placeholder_sbmac_duplex } sbmac_duplex ;

/* Variables and functions */
 int M_MAC_FC_CMD ; 
 int M_MAC_FC_SEL ; 
 int M_MAC_HDX_EN ; 
 int V_MAC_FC_CMD_DISABLED ; 
 int V_MAC_FC_CMD_ENABLED ; 
 int V_MAC_FC_CMD_ENAB_FALSECARR ; 
 int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 
#define  sbmac_duplex_full 133 
#define  sbmac_duplex_half 132 
#define  sbmac_fc_carrier 131 
#define  sbmac_fc_collision 130 
#define  sbmac_fc_disabled 129 
#define  sbmac_fc_frame 128 
 scalar_t__ sbmac_state_on ; 

__attribute__((used)) static int sbmac_set_duplex(struct sbmac_softc *s, enum sbmac_duplex duplex,
			    enum sbmac_fc fc)
{
	uint64_t cfg;

	/*
	 * Save new current values
	 */

	s->sbm_duplex = duplex;
	s->sbm_fc = fc;

	if (s->sbm_state == sbmac_state_on)
		return 0;	/* save for next restart */

	/*
	 * Read current register values
	 */

	cfg = __raw_readq(s->sbm_maccfg);

	/*
	 * Mask off the stuff we're about to change
	 */

	cfg &= ~(M_MAC_FC_SEL | M_MAC_FC_CMD | M_MAC_HDX_EN);


	switch (duplex) {
	case sbmac_duplex_half:
		switch (fc) {
		case sbmac_fc_disabled:
			cfg |= M_MAC_HDX_EN | V_MAC_FC_CMD_DISABLED;
			break;

		case sbmac_fc_collision:
			cfg |= M_MAC_HDX_EN | V_MAC_FC_CMD_ENABLED;
			break;

		case sbmac_fc_carrier:
			cfg |= M_MAC_HDX_EN | V_MAC_FC_CMD_ENAB_FALSECARR;
			break;

		case sbmac_fc_frame:		/* not valid in half duplex */
		default:			/* invalid selection */
			return 0;
		}
		break;

	case sbmac_duplex_full:
		switch (fc) {
		case sbmac_fc_disabled:
			cfg |= V_MAC_FC_CMD_DISABLED;
			break;

		case sbmac_fc_frame:
			cfg |= V_MAC_FC_CMD_ENABLED;
			break;

		case sbmac_fc_collision:	/* not valid in full duplex */
		case sbmac_fc_carrier:		/* not valid in full duplex */
		default:
			return 0;
		}
		break;
	default:
		return 0;
	}

	/*
	 * Send the bits back to the hardware
	 */

	__raw_writeq(cfg, s->sbm_maccfg);

	return 1;
}