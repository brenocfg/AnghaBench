#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lock_ops; int /*<<< orphan*/ * algo; struct intel_sdvo* algo_data; TYPE_2__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct intel_sdvo {TYPE_3__ ddc; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_sdvo_ddc_proxy ; 
 int /*<<< orphan*/  proxy_lock_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
intel_sdvo_init_ddc_proxy(struct intel_sdvo *sdvo,
			  struct drm_i915_private *dev_priv)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;

	sdvo->ddc.owner = THIS_MODULE;
	sdvo->ddc.class = I2C_CLASS_DDC;
	snprintf(sdvo->ddc.name, I2C_NAME_SIZE, "SDVO DDC proxy");
	sdvo->ddc.dev.parent = &pdev->dev;
	sdvo->ddc.algo_data = sdvo;
	sdvo->ddc.algo = &intel_sdvo_ddc_proxy;
	sdvo->ddc.lock_ops = &proxy_lock_ops;

	return i2c_add_adapter(&sdvo->ddc) == 0;
}