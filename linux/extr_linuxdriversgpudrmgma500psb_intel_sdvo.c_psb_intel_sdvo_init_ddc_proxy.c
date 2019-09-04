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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int /*<<< orphan*/ * algo; struct psb_intel_sdvo* algo_data; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct psb_intel_sdvo {TYPE_3__ ddc; } ;
struct drm_device {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  psb_intel_sdvo_ddc_proxy ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
psb_intel_sdvo_init_ddc_proxy(struct psb_intel_sdvo *sdvo,
			  struct drm_device *dev)
{
	sdvo->ddc.owner = THIS_MODULE;
	sdvo->ddc.class = I2C_CLASS_DDC;
	snprintf(sdvo->ddc.name, I2C_NAME_SIZE, "SDVO DDC proxy");
	sdvo->ddc.dev.parent = &dev->pdev->dev;
	sdvo->ddc.algo_data = sdvo;
	sdvo->ddc.algo = &psb_intel_sdvo_ddc_proxy;

	return i2c_add_adapter(&sdvo->ddc) == 0;
}