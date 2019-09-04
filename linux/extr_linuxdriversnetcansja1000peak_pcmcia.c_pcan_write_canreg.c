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
typedef  int u8 ;
struct sja1000_priv {int reg_base; struct pcan_pccard* priv; } ;
struct pcan_pccard {int ioport_addr; } ;

/* Variables and functions */
#define  MOD_RM 128 
 int PCC_CHAN_SIZE ; 
 int /*<<< orphan*/  PCC_LED (int) ; 
 int /*<<< orphan*/  PCC_LED_ON ; 
 int /*<<< orphan*/  PCC_LED_SLOW ; 
 int SJA1000_MOD ; 
 int /*<<< orphan*/  iowrite8 (int,int) ; 
 int /*<<< orphan*/  pcan_set_leds (struct pcan_pccard*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_start_led_timer (struct pcan_pccard*) ; 

__attribute__((used)) static void pcan_write_canreg(const struct sja1000_priv *priv, int port, u8 v)
{
	struct pcan_pccard *card = priv->priv;
	int c = (priv->reg_base - card->ioport_addr) / PCC_CHAN_SIZE;

	/* sja1000 register changes control the leds state */
	if (port == SJA1000_MOD)
		switch (v) {
		case MOD_RM:
			/* Reset Mode: set led on */
			pcan_set_leds(card, PCC_LED(c), PCC_LED_ON);
			break;
		case 0x00:
			/* Normal Mode: led slow blinking and start led timer */
			pcan_set_leds(card, PCC_LED(c), PCC_LED_SLOW);
			pcan_start_led_timer(card);
			break;
		default:
			break;
		}

	iowrite8(v, priv->reg_base + port);
}