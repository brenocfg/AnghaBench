#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ocotp_priv {TYPE_1__* data; struct device* dev; int /*<<< orphan*/  nvmem_ipc; } ;
struct nvmem_device {int dummy; } ;
struct TYPE_5__ {int size; struct ocotp_priv* priv; struct device* dev; } ;
struct TYPE_4__ {int nregs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct nvmem_device*) ; 
 struct ocotp_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (struct device*,TYPE_2__*) ; 
 int imx_scu_get_handle (int /*<<< orphan*/ *) ; 
 TYPE_2__ imx_scu_ocotp_nvmem_config ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int imx_scu_ocotp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ocotp_priv *priv;
	struct nvmem_device *nvmem;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = imx_scu_get_handle(&priv->nvmem_ipc);
	if (ret)
		return ret;

	priv->data = of_device_get_match_data(dev);
	priv->dev = dev;
	imx_scu_ocotp_nvmem_config.size = 4 * priv->data->nregs;
	imx_scu_ocotp_nvmem_config.dev = dev;
	imx_scu_ocotp_nvmem_config.priv = priv;
	nvmem = devm_nvmem_register(dev, &imx_scu_ocotp_nvmem_config);

	return PTR_ERR_OR_ZERO(nvmem);
}