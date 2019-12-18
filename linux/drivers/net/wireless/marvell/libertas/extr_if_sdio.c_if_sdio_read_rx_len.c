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
typedef  int u16 ;
struct if_sdio_card {int model; int rx_unit; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_SDIO_RX_LEN ; 
#define  MODEL_8385 130 
#define  MODEL_8686 129 
#define  MODEL_8688 128 
 int if_sdio_read_scratch (struct if_sdio_card*,int*) ; 
 int sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u16 if_sdio_read_rx_len(struct if_sdio_card *card, int *err)
{
	int ret;
	u16 rx_len;

	switch (card->model) {
	case MODEL_8385:
	case MODEL_8686:
		rx_len = if_sdio_read_scratch(card, &ret);
		break;
	case MODEL_8688:
	default: /* for newer chipsets */
		rx_len = sdio_readb(card->func, IF_SDIO_RX_LEN, &ret);
		if (!ret)
			rx_len <<= card->rx_unit;
		else
			rx_len = 0xffff;	/* invalid length */

		break;
	}

	if (err)
		*err = ret;

	return rx_len;
}