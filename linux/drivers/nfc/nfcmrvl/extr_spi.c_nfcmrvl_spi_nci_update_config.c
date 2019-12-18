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
struct nfcmrvl_spi_drv_data {TYPE_1__* nci_spi; } ;
struct nfcmrvl_private {struct nfcmrvl_spi_drv_data* drv_data; } ;
struct nfcmrvl_fw_spi_config {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfer_speed_hz; } ;

/* Variables and functions */

__attribute__((used)) static void nfcmrvl_spi_nci_update_config(struct nfcmrvl_private *priv,
					  const void *param)
{
	struct nfcmrvl_spi_drv_data *drv_data = priv->drv_data;
	const struct nfcmrvl_fw_spi_config *config = param;

	drv_data->nci_spi->xfer_speed_hz = config->clk;
}