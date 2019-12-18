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
struct nfcmrvl_private {struct nci_uart* drv_data; } ;
struct nfcmrvl_fw_uart_config {int /*<<< orphan*/  flow_control; int /*<<< orphan*/  baudrate; } ;
struct nci_uart {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_uart_set_config (struct nci_uart*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfcmrvl_uart_nci_update_config(struct nfcmrvl_private *priv,
					   const void *param)
{
	struct nci_uart *nu = priv->drv_data;
	const struct nfcmrvl_fw_uart_config *config = param;

	nci_uart_set_config(nu, le32_to_cpu(config->baudrate),
			    config->flow_control);
}