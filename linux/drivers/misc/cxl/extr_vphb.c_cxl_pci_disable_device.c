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
struct TYPE_3__ {int /*<<< orphan*/ * cxl_ctx; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct cxl_context {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ STARTED ; 
 struct cxl_context* cxl_get_context (struct pci_dev*) ; 
 int /*<<< orphan*/  cxl_release_context (struct cxl_context*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 

__attribute__((used)) static void cxl_pci_disable_device(struct pci_dev *dev)
{
	struct cxl_context *ctx = cxl_get_context(dev);

	if (ctx) {
		if (ctx->status == STARTED) {
			dev_err(&dev->dev, "Default context started\n");
			return;
		}
		dev->dev.archdata.cxl_ctx = NULL;
		cxl_release_context(ctx);
	}
}