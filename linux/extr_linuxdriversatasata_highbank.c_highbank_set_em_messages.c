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
struct ecx_plat_data {int* sgpio_gpio; scalar_t__ post_clocks; scalar_t__ pre_clocks; int /*<<< orphan*/  n_ports; int /*<<< orphan*/  port_to_sgpio; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct ata_port_info {int flags; } ;
struct ahci_host_priv {int em_buf_sz; int /*<<< orphan*/  em_msg_type; scalar_t__ em_loc; struct ecx_plat_data* plat_data; } ;

/* Variables and functions */
 int ATA_FLAG_EM ; 
 int ATA_FLAG_SW_ACTIVITY ; 
 int /*<<< orphan*/  EM_MSG_TYPE_LED ; 
 int SGPIO_PINS ; 
 int /*<<< orphan*/  gpio_direction_output (int,int) ; 
 int gpio_request (int,char*) ; 
 int of_get_named_gpio (struct device_node*,char*,int) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static void highbank_set_em_messages(struct device *dev,
					struct ahci_host_priv *hpriv,
					struct ata_port_info *pi)
{
	struct device_node *np = dev->of_node;
	struct ecx_plat_data *pdata = hpriv->plat_data;
	int i;
	int err;

	for (i = 0; i < SGPIO_PINS; i++) {
		err = of_get_named_gpio(np, "calxeda,sgpio-gpio", i);
		if (err < 0)
			return;

		pdata->sgpio_gpio[i] = err;
		err = gpio_request(pdata->sgpio_gpio[i], "CX SGPIO");
		if (err) {
			pr_err("sata_highbank gpio_request %d failed: %d\n",
					i, err);
			return;
		}
		gpio_direction_output(pdata->sgpio_gpio[i], 1);
	}
	of_property_read_u32_array(np, "calxeda,led-order",
						pdata->port_to_sgpio,
						pdata->n_ports);
	if (of_property_read_u32(np, "calxeda,pre-clocks", &pdata->pre_clocks))
		pdata->pre_clocks = 0;
	if (of_property_read_u32(np, "calxeda,post-clocks",
				&pdata->post_clocks))
		pdata->post_clocks = 0;

	/* store em_loc */
	hpriv->em_loc = 0;
	hpriv->em_buf_sz = 4;
	hpriv->em_msg_type = EM_MSG_TYPE_LED;
	pi->flags |= ATA_FLAG_EM | ATA_FLAG_SW_ACTIVITY;
}