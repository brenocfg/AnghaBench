#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvdimm_bus_descriptor {int dummy; } ;
struct nvdimm_bus {int dummy; } ;
struct nvdimm {int dummy; } ;
struct nfit_mem {TYPE_6__* memdev_dcr; int /*<<< orphan*/  idt_dcr; TYPE_5__* spa_dcr; TYPE_4__* dcr; TYPE_2__* memdev_bdw; int /*<<< orphan*/  idt_bdw; TYPE_5__* spa_bdw; TYPE_1__* bdw; } ;
struct TYPE_9__ {scalar_t__ base; } ;
struct nfit_blk_mmio {int line_size; TYPE_5__* spa; int /*<<< orphan*/  idt; int /*<<< orphan*/  base_offset; int /*<<< orphan*/  size; TYPE_3__ addr; } ;
struct nfit_blk {scalar_t__ stat_offset; scalar_t__ cmd_offset; int /*<<< orphan*/  nd_region; struct nfit_blk_mmio* mmio; int /*<<< orphan*/  bdw_offset; } ;
struct nd_blk_region {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  interleave_ways; int /*<<< orphan*/  region_offset; } ;
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct TYPE_10__ {int /*<<< orphan*/  window_size; scalar_t__ status_offset; scalar_t__ command_offset; } ;
struct TYPE_8__ {int /*<<< orphan*/  interleave_ways; int /*<<< orphan*/  region_offset; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 size_t BDW ; 
 size_t DCR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int acpi_nfit_blk_get_flags (struct nvdimm_bus_descriptor*,struct nvdimm*,struct nfit_blk*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct nfit_blk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_nvdimm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_nvdimm_memremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_blk_memremap_flags (struct nd_blk_region*) ; 
 int /*<<< orphan*/  nd_blk_region_set_provider_data (struct nd_blk_region*,struct nfit_blk*) ; 
 struct nvdimm* nd_blk_region_to_dimm (struct nd_blk_region*) ; 
 int nfit_blk_init_interleave (struct nfit_blk_mmio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvdimm_has_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_name (struct nvdimm*) ; 
 struct nfit_mem* nvdimm_provider_data (struct nvdimm*) ; 
 struct nd_blk_region* to_nd_blk_region (struct device*) ; 
 struct nvdimm_bus_descriptor* to_nd_desc (struct nvdimm_bus*) ; 
 int /*<<< orphan*/  to_nd_region (struct device*) ; 

__attribute__((used)) static int acpi_nfit_blk_region_enable(struct nvdimm_bus *nvdimm_bus,
		struct device *dev)
{
	struct nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	struct nd_blk_region *ndbr = to_nd_blk_region(dev);
	struct nfit_blk_mmio *mmio;
	struct nfit_blk *nfit_blk;
	struct nfit_mem *nfit_mem;
	struct nvdimm *nvdimm;
	int rc;

	nvdimm = nd_blk_region_to_dimm(ndbr);
	nfit_mem = nvdimm_provider_data(nvdimm);
	if (!nfit_mem || !nfit_mem->dcr || !nfit_mem->bdw) {
		dev_dbg(dev, "missing%s%s%s\n",
				nfit_mem ? "" : " nfit_mem",
				(nfit_mem && nfit_mem->dcr) ? "" : " dcr",
				(nfit_mem && nfit_mem->bdw) ? "" : " bdw");
		return -ENXIO;
	}

	nfit_blk = devm_kzalloc(dev, sizeof(*nfit_blk), GFP_KERNEL);
	if (!nfit_blk)
		return -ENOMEM;
	nd_blk_region_set_provider_data(ndbr, nfit_blk);
	nfit_blk->nd_region = to_nd_region(dev);

	/* map block aperture memory */
	nfit_blk->bdw_offset = nfit_mem->bdw->offset;
	mmio = &nfit_blk->mmio[BDW];
	mmio->addr.base = devm_nvdimm_memremap(dev, nfit_mem->spa_bdw->address,
                        nfit_mem->spa_bdw->length, nd_blk_memremap_flags(ndbr));
	if (!mmio->addr.base) {
		dev_dbg(dev, "%s failed to map bdw\n",
				nvdimm_name(nvdimm));
		return -ENOMEM;
	}
	mmio->size = nfit_mem->bdw->size;
	mmio->base_offset = nfit_mem->memdev_bdw->region_offset;
	mmio->idt = nfit_mem->idt_bdw;
	mmio->spa = nfit_mem->spa_bdw;
	rc = nfit_blk_init_interleave(mmio, nfit_mem->idt_bdw,
			nfit_mem->memdev_bdw->interleave_ways);
	if (rc) {
		dev_dbg(dev, "%s failed to init bdw interleave\n",
				nvdimm_name(nvdimm));
		return rc;
	}

	/* map block control memory */
	nfit_blk->cmd_offset = nfit_mem->dcr->command_offset;
	nfit_blk->stat_offset = nfit_mem->dcr->status_offset;
	mmio = &nfit_blk->mmio[DCR];
	mmio->addr.base = devm_nvdimm_ioremap(dev, nfit_mem->spa_dcr->address,
			nfit_mem->spa_dcr->length);
	if (!mmio->addr.base) {
		dev_dbg(dev, "%s failed to map dcr\n",
				nvdimm_name(nvdimm));
		return -ENOMEM;
	}
	mmio->size = nfit_mem->dcr->window_size;
	mmio->base_offset = nfit_mem->memdev_dcr->region_offset;
	mmio->idt = nfit_mem->idt_dcr;
	mmio->spa = nfit_mem->spa_dcr;
	rc = nfit_blk_init_interleave(mmio, nfit_mem->idt_dcr,
			nfit_mem->memdev_dcr->interleave_ways);
	if (rc) {
		dev_dbg(dev, "%s failed to init dcr interleave\n",
				nvdimm_name(nvdimm));
		return rc;
	}

	rc = acpi_nfit_blk_get_flags(nd_desc, nvdimm, nfit_blk);
	if (rc < 0) {
		dev_dbg(dev, "%s failed get DIMM flags\n",
				nvdimm_name(nvdimm));
		return rc;
	}

	if (nvdimm_has_flush(nfit_blk->nd_region) < 0)
		dev_warn(dev, "unable to guarantee persistence of writes\n");

	if (mmio->line_size == 0)
		return 0;

	if ((u32) nfit_blk->cmd_offset % mmio->line_size
			+ 8 > mmio->line_size) {
		dev_dbg(dev, "cmd_offset crosses interleave boundary\n");
		return -ENXIO;
	} else if ((u32) nfit_blk->stat_offset % mmio->line_size
			+ 8 > mmio->line_size) {
		dev_dbg(dev, "stat_offset crosses interleave boundary\n");
		return -ENXIO;
	}

	return 0;
}