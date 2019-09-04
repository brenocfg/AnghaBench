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
typedef  int u32 ;
struct seattle_plat_data {int /*<<< orphan*/  sgpio_ctrl; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ata_port_info {int dummy; } ;
struct ahci_host_priv {int em_buf_sz; struct seattle_plat_data* plat_data; int /*<<< orphan*/  em_msg_type; scalar_t__ em_loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM_MSG_TYPE_LED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct ata_port_info const ahci_port_info ; 
 struct ata_port_info const ahci_port_seattle_info ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,int /*<<< orphan*/ ) ; 
 struct seattle_plat_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const struct ata_port_info *ahci_seattle_get_port_info(
		struct platform_device *pdev, struct ahci_host_priv *hpriv)
{
	struct device *dev = &pdev->dev;
	struct seattle_plat_data *plat_data;
	u32 val;

	plat_data = devm_kzalloc(dev, sizeof(*plat_data), GFP_KERNEL);
	if (!plat_data)
		return &ahci_port_info;

	plat_data->sgpio_ctrl = devm_ioremap_resource(dev,
			      platform_get_resource(pdev, IORESOURCE_MEM, 1));
	if (IS_ERR(plat_data->sgpio_ctrl))
		return &ahci_port_info;

	val = ioread32(plat_data->sgpio_ctrl);

	if (!(val & 0xf))
		return &ahci_port_info;

	hpriv->em_loc = 0;
	hpriv->em_buf_sz = 4;
	hpriv->em_msg_type = EM_MSG_TYPE_LED;
	hpriv->plat_data = plat_data;

	dev_info(dev, "SGPIO LED control is enabled.\n");
	return &ahci_port_seattle_info;
}