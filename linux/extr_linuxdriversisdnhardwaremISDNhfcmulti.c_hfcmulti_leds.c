#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hfc_multi {int leds; size_t* dnum; int e1_state; int* flash; int activity_tx; int activity_rx; int ledstate; int /*<<< orphan*/  pci_iobase; TYPE_1__* chan; int /*<<< orphan*/  chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_6__ {TYPE_2__ D; } ;
struct dchannel {int state; TYPE_3__ dev; } ;
struct TYPE_4__ {struct dchannel* dch; int /*<<< orphan*/  los; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFC_CHIP_B410P ; 
 int /*<<< orphan*/  HFC_outb_nodebug (struct hfc_multi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISDN_P_NT_S0 ; 
 int /*<<< orphan*/  R_BRG_PCM_CFG ; 
 int /*<<< orphan*/  R_GPIO_EN1 ; 
 int /*<<< orphan*/  R_GPIO_OUT1 ; 
 int V_PCM_CLK ; 
 int /*<<< orphan*/  outl (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 void* poll ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpm_out (struct hfc_multi*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
hfcmulti_leds(struct hfc_multi *hc)
{
	unsigned long lled;
	unsigned long leddw;
	int i, state, active, leds;
	struct dchannel *dch;
	int led[4];

	switch (hc->leds) {
	case 1: /* HFC-E1 OEM */
		/* 2 red steady:       LOS
		 * 1 red steady:       L1 not active
		 * 2 green steady:     L1 active
		 * 1st green flashing: activity on TX
		 * 2nd green flashing: activity on RX
		 */
		led[0] = 0;
		led[1] = 0;
		led[2] = 0;
		led[3] = 0;
		dch = hc->chan[hc->dnum[0]].dch;
		if (dch) {
			if (hc->chan[hc->dnum[0]].los)
				led[1] = 1;
			if (hc->e1_state != 1) {
				led[0] = 1;
				hc->flash[2] = 0;
				hc->flash[3] = 0;
			} else {
				led[2] = 1;
				led[3] = 1;
				if (!hc->flash[2] && hc->activity_tx)
					hc->flash[2] = poll;
				if (!hc->flash[3] && hc->activity_rx)
					hc->flash[3] = poll;
				if (hc->flash[2] && hc->flash[2] < 1024)
					led[2] = 0;
				if (hc->flash[3] && hc->flash[3] < 1024)
					led[3] = 0;
				if (hc->flash[2] >= 2048)
					hc->flash[2] = 0;
				if (hc->flash[3] >= 2048)
					hc->flash[3] = 0;
				if (hc->flash[2])
					hc->flash[2] += poll;
				if (hc->flash[3])
					hc->flash[3] += poll;
			}
		}
		leds = (led[0] | (led[1]<<2) | (led[2]<<1) | (led[3]<<3))^0xF;
		/* leds are inverted */
		if (leds != (int)hc->ledstate) {
			HFC_outb_nodebug(hc, R_GPIO_OUT1, leds);
			hc->ledstate = leds;
		}
		break;

	case 2: /* HFC-4S OEM */
		/* red steady:     PH_DEACTIVATE
		 * green steady:   PH_ACTIVATE
		 * green flashing: activity on TX
		 */
		for (i = 0; i < 4; i++) {
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			if (dch) {
				state = dch->state;
				if (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				else
					active = 7;
			}
			if (state) {
				if (state == active) {
					led[i] = 1; /* led green */
					hc->activity_tx |= hc->activity_rx;
					if (!hc->flash[i] &&
						(hc->activity_tx & (1 << i)))
							hc->flash[i] = poll;
					if (hc->flash[i] && hc->flash[i] < 1024)
						led[i] = 0; /* led off */
					if (hc->flash[i] >= 2048)
						hc->flash[i] = 0;
					if (hc->flash[i])
						hc->flash[i] += poll;
				} else {
					led[i] = 2; /* led red */
					hc->flash[i] = 0;
				}
			} else
				led[i] = 0; /* led off */
		}
		if (test_bit(HFC_CHIP_B410P, &hc->chip)) {
			leds = 0;
			for (i = 0; i < 4; i++) {
				if (led[i] == 1) {
					/*green*/
					leds |= (0x2 << (i * 2));
				} else if (led[i] == 2) {
					/*red*/
					leds |= (0x1 << (i * 2));
				}
			}
			if (leds != (int)hc->ledstate) {
				vpm_out(hc, 0, 0x1a8 + 3, leds);
				hc->ledstate = leds;
			}
		} else {
			leds = ((led[3] > 0) << 0) | ((led[1] > 0) << 1) |
				((led[0] > 0) << 2) | ((led[2] > 0) << 3) |
				((led[3] & 1) << 4) | ((led[1] & 1) << 5) |
				((led[0] & 1) << 6) | ((led[2] & 1) << 7);
			if (leds != (int)hc->ledstate) {
				HFC_outb_nodebug(hc, R_GPIO_EN1, leds & 0x0F);
				HFC_outb_nodebug(hc, R_GPIO_OUT1, leds >> 4);
				hc->ledstate = leds;
			}
		}
		break;

	case 3: /* HFC 1S/2S Beronet */
		/* red steady:     PH_DEACTIVATE
		 * green steady:   PH_ACTIVATE
		 * green flashing: activity on TX
		 */
		for (i = 0; i < 2; i++) {
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			if (dch) {
				state = dch->state;
				if (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				else
					active = 7;
			}
			if (state) {
				if (state == active) {
					led[i] = 1; /* led green */
					hc->activity_tx |= hc->activity_rx;
					if (!hc->flash[i] &&
						(hc->activity_tx & (1 << i)))
							hc->flash[i] = poll;
					if (hc->flash[i] < 1024)
						led[i] = 0; /* led off */
					if (hc->flash[i] >= 2048)
						hc->flash[i] = 0;
					if (hc->flash[i])
						hc->flash[i] += poll;
				} else {
					led[i] = 2; /* led red */
					hc->flash[i] = 0;
				}
			} else
				led[i] = 0; /* led off */
		}
		leds = (led[0] > 0) | ((led[1] > 0) << 1) | ((led[0]&1) << 2)
			| ((led[1]&1) << 3);
		if (leds != (int)hc->ledstate) {
			HFC_outb_nodebug(hc, R_GPIO_EN1,
					 ((led[0] > 0) << 2) | ((led[1] > 0) << 3));
			HFC_outb_nodebug(hc, R_GPIO_OUT1,
					 ((led[0] & 1) << 2) | ((led[1] & 1) << 3));
			hc->ledstate = leds;
		}
		break;
	case 8: /* HFC 8S+ Beronet */
		/* off:      PH_DEACTIVATE
		 * steady:   PH_ACTIVATE
		 * flashing: activity on TX
		 */
		lled = 0xff; /* leds off */
		for (i = 0; i < 8; i++) {
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			if (dch) {
				state = dch->state;
				if (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				else
					active = 7;
			}
			if (state) {
				if (state == active) {
					lled &= ~(1 << i); /* led on */
					hc->activity_tx |= hc->activity_rx;
					if (!hc->flash[i] &&
						(hc->activity_tx & (1 << i)))
							hc->flash[i] = poll;
					if (hc->flash[i] < 1024)
						lled |= 1 << i; /* led off */
					if (hc->flash[i] >= 2048)
						hc->flash[i] = 0;
					if (hc->flash[i])
						hc->flash[i] += poll;
				} else
					hc->flash[i] = 0;
			}
		}
		leddw = lled << 24 | lled << 16 | lled << 8 | lled;
		if (leddw != hc->ledstate) {
			/* HFC_outb(hc, R_BRG_PCM_CFG, 1);
			   HFC_outb(c, R_BRG_PCM_CFG, (0x0 << 6) | 0x3); */
			/* was _io before */
			HFC_outb_nodebug(hc, R_BRG_PCM_CFG, 1 | V_PCM_CLK);
			outw(0x4000, hc->pci_iobase + 4);
			outl(leddw, hc->pci_iobase);
			HFC_outb_nodebug(hc, R_BRG_PCM_CFG, V_PCM_CLK);
			hc->ledstate = leddw;
		}
		break;
	}
	hc->activity_tx = 0;
	hc->activity_rx = 0;
}