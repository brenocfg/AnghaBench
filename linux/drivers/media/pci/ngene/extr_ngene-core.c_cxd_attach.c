#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ngene_ci {struct ngene* dev; int /*<<< orphan*/  en; } ;
struct ngene {TYPE_2__* channel; struct ngene_ci ci; TYPE_1__* pci_dev; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct cxd2099_cfg {int /*<<< orphan*/ * en; } ;
struct TYPE_4__ {struct i2c_client** i2c_client; int /*<<< orphan*/  i2c_adapter; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 struct cxd2099_cfg cxd_cfgtmpl ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct i2c_client* dvb_module_probe (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct cxd2099_cfg*) ; 
 int ngene_port_has_cxd2099 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void cxd_attach(struct ngene *dev)
{
	struct device *pdev = &dev->pci_dev->dev;
	struct ngene_ci *ci = &dev->ci;
	struct cxd2099_cfg cxd_cfg = cxd_cfgtmpl;
	struct i2c_client *client;
	int ret;
	u8 type;

	/* check for CXD2099AR presence before attaching */
	ret = ngene_port_has_cxd2099(&dev->channel[0].i2c_adapter, &type);
	if (!ret) {
		dev_dbg(pdev, "No CXD2099AR found\n");
		return;
	}

	if (type != 1) {
		dev_warn(pdev, "CXD2099AR is uninitialized!\n");
		return;
	}

	cxd_cfg.en = &ci->en;
	client = dvb_module_probe("cxd2099", NULL,
				  &dev->channel[0].i2c_adapter,
				  0x40, &cxd_cfg);
	if (!client)
		goto err;

	ci->dev = dev;
	dev->channel[0].i2c_client[0] = client;
	return;

err:
	dev_err(pdev, "CXD2099AR attach failed\n");
	return;
}