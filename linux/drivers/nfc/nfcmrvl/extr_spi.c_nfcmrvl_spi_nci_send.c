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
struct sk_buff {int dummy; } ;
struct nfcmrvl_spi_drv_data {int /*<<< orphan*/  handshake_completion; int /*<<< orphan*/  nci_spi; int /*<<< orphan*/  flags; } ;
struct nfcmrvl_private {int /*<<< orphan*/  dev; struct nfcmrvl_spi_drv_data* drv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_WAIT_HANDSHAKE ; 
 int nci_spi_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int nfcmrvl_spi_nci_send(struct nfcmrvl_private *priv,
				struct sk_buff *skb)
{
	struct nfcmrvl_spi_drv_data *drv_data = priv->drv_data;
	int err;

	/* Reinit completion for slave handshake */
	reinit_completion(&drv_data->handshake_completion);
	set_bit(SPI_WAIT_HANDSHAKE, &drv_data->flags);

	/*
	 * Append a dummy byte at the end of SPI frame. This is due to a
	 * specific DMA implementation in the controller
	 */
	skb_put(skb, 1);

	/* Send the SPI packet */
	err = nci_spi_send(drv_data->nci_spi, &drv_data->handshake_completion,
			   skb);
	if (err)
		nfc_err(priv->dev, "spi_send failed %d", err);

	return err;
}