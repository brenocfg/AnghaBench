#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  reset_n_io; } ;
struct nfcmrvl_private {int /*<<< orphan*/  dev; TYPE_1__ config; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFCMRVL_PHY_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void nfcmrvl_chip_reset(struct nfcmrvl_private *priv)
{
	/* Reset possible fault of previous session */
	clear_bit(NFCMRVL_PHY_ERROR, &priv->flags);

	if (gpio_is_valid(priv->config.reset_n_io)) {
		nfc_info(priv->dev, "reset the chip\n");
		gpio_set_value(priv->config.reset_n_io, 0);
		usleep_range(5000, 10000);
		gpio_set_value(priv->config.reset_n_io, 1);
	} else
		nfc_info(priv->dev, "no reset available on this interface\n");
}