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
typedef  int /*<<< orphan*/  u32 ;
struct ftgmac100 {int cur_speed; scalar_t__ tx_pointer; scalar_t__ tx_clean_pointer; scalar_t__ rx_pointer; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FTGMAC100_MACCR_FAST_MODE ; 
 int /*<<< orphan*/  FTGMAC100_MACCR_GIGA_MODE ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int ftgmac100_reset_mac (struct ftgmac100*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ftgmac100_reset_and_config_mac(struct ftgmac100 *priv)
{
	u32 maccr = 0;

	switch (priv->cur_speed) {
	case SPEED_10:
	case 0: /* no link */
		break;

	case SPEED_100:
		maccr |= FTGMAC100_MACCR_FAST_MODE;
		break;

	case SPEED_1000:
		maccr |= FTGMAC100_MACCR_GIGA_MODE;
		break;
	default:
		netdev_err(priv->netdev, "Unknown speed %d !\n",
			   priv->cur_speed);
		break;
	}

	/* (Re)initialize the queue pointers */
	priv->rx_pointer = 0;
	priv->tx_clean_pointer = 0;
	priv->tx_pointer = 0;

	/* The doc says reset twice with 10us interval */
	if (ftgmac100_reset_mac(priv, maccr))
		return -EIO;
	usleep_range(10, 1000);
	return ftgmac100_reset_mac(priv, maccr);
}