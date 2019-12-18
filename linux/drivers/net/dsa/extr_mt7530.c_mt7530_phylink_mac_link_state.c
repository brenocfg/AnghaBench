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
typedef  int u32 ;
struct phylink_link_state {int link; int an_complete; int duplex; int pause; int /*<<< orphan*/  speed; } ;
struct mt7530_priv {int dummy; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLO_PAUSE_RX ; 
 int MLO_PAUSE_TX ; 
 int MT7530_NUM_PORTS ; 
 int /*<<< orphan*/  MT7530_PMSR_P (int) ; 
 int PMSR_DPX ; 
 int PMSR_LINK ; 
 int PMSR_RX_FC ; 
#define  PMSR_SPEED_10 130 
#define  PMSR_SPEED_100 129 
#define  PMSR_SPEED_1000 128 
 int PMSR_SPEED_MASK ; 
 int PMSR_TX_FC ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int mt7530_read (struct mt7530_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7530_phylink_mac_link_state(struct dsa_switch *ds, int port,
			      struct phylink_link_state *state)
{
	struct mt7530_priv *priv = ds->priv;
	u32 pmsr;

	if (port < 0 || port >= MT7530_NUM_PORTS)
		return -EINVAL;

	pmsr = mt7530_read(priv, MT7530_PMSR_P(port));

	state->link = (pmsr & PMSR_LINK);
	state->an_complete = state->link;
	state->duplex = !!(pmsr & PMSR_DPX);

	switch (pmsr & PMSR_SPEED_MASK) {
	case PMSR_SPEED_10:
		state->speed = SPEED_10;
		break;
	case PMSR_SPEED_100:
		state->speed = SPEED_100;
		break;
	case PMSR_SPEED_1000:
		state->speed = SPEED_1000;
		break;
	default:
		state->speed = SPEED_UNKNOWN;
		break;
	}

	state->pause &= ~(MLO_PAUSE_RX | MLO_PAUSE_TX);
	if (pmsr & PMSR_RX_FC)
		state->pause |= MLO_PAUSE_RX;
	if (pmsr & PMSR_TX_FC)
		state->pause |= MLO_PAUSE_TX;

	return 1;
}