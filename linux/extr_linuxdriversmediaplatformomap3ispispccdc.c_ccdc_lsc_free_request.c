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
struct TYPE_4__ {int /*<<< orphan*/  dma; scalar_t__ addr; int /*<<< orphan*/  sgt; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct ispccdc_lsc_config_req {TYPE_2__ table; TYPE_1__ config; } ;
struct isp_device {int /*<<< orphan*/  dev; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ispccdc_lsc_config_req*) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static void ccdc_lsc_free_request(struct isp_ccdc_device *ccdc,
				  struct ispccdc_lsc_config_req *req)
{
	struct isp_device *isp = to_isp_device(ccdc);

	if (req == NULL)
		return;

	if (req->table.addr) {
		sg_free_table(&req->table.sgt);
		dma_free_coherent(isp->dev, req->config.size, req->table.addr,
				  req->table.dma);
	}

	kfree(req);
}