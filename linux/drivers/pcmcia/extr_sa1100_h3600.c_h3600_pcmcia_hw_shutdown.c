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
struct soc_pcmcia_socket {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  H3XXX_EGPIO_CARD_RESET ; 
 int /*<<< orphan*/  H3XXX_EGPIO_OPT_NVRAM_ON ; 
 int /*<<< orphan*/  H3XXX_EGPIO_OPT_ON ; 
 int /*<<< orphan*/  H3XXX_EGPIO_OPT_RESET ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void h3600_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	switch (skt->nr) {
	case 0:
		/* Disable CF bus: */
		gpio_set_value(H3XXX_EGPIO_OPT_NVRAM_ON, 0);
		gpio_set_value(H3XXX_EGPIO_OPT_ON, 0);
		gpio_set_value(H3XXX_EGPIO_OPT_RESET, 1);

		gpio_free(H3XXX_EGPIO_CARD_RESET);
		gpio_free(H3XXX_EGPIO_OPT_RESET);
		gpio_free(H3XXX_EGPIO_OPT_ON);
		gpio_free(H3XXX_EGPIO_OPT_NVRAM_ON);
		break;
	case 1:
		break;
	}
}