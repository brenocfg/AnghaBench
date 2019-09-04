#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct nvif_object {int dummy; } ;
struct nv_sim_state {int pclk_khz; int mclk_khz; int nvclk_khz; int bpp; int memory_type; int memory_width; int mem_latency; int mem_page_miss; int /*<<< orphan*/  two_heads; } ;
struct nv_fifo_info {int burst; int lwm; } ;
struct TYPE_6__ {scalar_t__ family; } ;
struct TYPE_7__ {TYPE_2__ info; struct nvif_object object; } ;
struct TYPE_8__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_4__ client; } ;
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_5__ {int device; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFB_CFG0 ; 
 int /*<<< orphan*/  NV04_PFB_CFG1 ; 
 scalar_t__ NV_DEVICE_INFO_V0_TNT ; 
 int /*<<< orphan*/  NV_PEXTDEV_BOOT_0 ; 
 int /*<<< orphan*/  PLL_CORE ; 
 int /*<<< orphan*/  PLL_MEMORY ; 
 int ilog2 (int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int nouveau_hw_get_clock (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_calc_arb (struct nv_fifo_info*,struct nv_sim_state*) ; 
 int /*<<< orphan*/  nv10_calc_arb (struct nv_fifo_info*,struct nv_sim_state*) ; 
 int /*<<< orphan*/  nv_two_heads (struct drm_device*) ; 
 int nvif_rd32 (struct nvif_object*,int /*<<< orphan*/ ) ; 
 int pci_domain_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain_bus_and_slot (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void
nv04_update_arb(struct drm_device *dev, int VClk, int bpp,
		int *burst, int *lwm)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvif_object *device = &nouveau_drm(dev)->client.device.object;
	struct nv_fifo_info fifo_data;
	struct nv_sim_state sim_data;
	int MClk = nouveau_hw_get_clock(dev, PLL_MEMORY);
	int NVClk = nouveau_hw_get_clock(dev, PLL_CORE);
	uint32_t cfg1 = nvif_rd32(device, NV04_PFB_CFG1);

	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	sim_data.bpp = bpp;
	sim_data.two_heads = nv_two_heads(dev);
	if ((dev->pdev->device & 0xffff) == 0x01a0 /*CHIPSET_NFORCE*/ ||
	    (dev->pdev->device & 0xffff) == 0x01f0 /*CHIPSET_NFORCE2*/) {
		uint32_t type;
		int domain = pci_domain_nr(dev->pdev->bus);

		pci_read_config_dword(pci_get_domain_bus_and_slot(domain, 0, 1),
				      0x7c, &type);

		sim_data.memory_type = (type >> 12) & 1;
		sim_data.memory_width = 64;
		sim_data.mem_latency = 3;
		sim_data.mem_page_miss = 10;
	} else {
		sim_data.memory_type = nvif_rd32(device, NV04_PFB_CFG0) & 0x1;
		sim_data.memory_width = (nvif_rd32(device, NV_PEXTDEV_BOOT_0) & 0x10) ? 128 : 64;
		sim_data.mem_latency = cfg1 & 0xf;
		sim_data.mem_page_miss = ((cfg1 >> 4) & 0xf) + ((cfg1 >> 31) & 0x1);
	}

	if (drm->client.device.info.family == NV_DEVICE_INFO_V0_TNT)
		nv04_calc_arb(&fifo_data, &sim_data);
	else
		nv10_calc_arb(&fifo_data, &sim_data);

	*burst = ilog2(fifo_data.burst >> 4);
	*lwm = fifo_data.lwm >> 3;
}