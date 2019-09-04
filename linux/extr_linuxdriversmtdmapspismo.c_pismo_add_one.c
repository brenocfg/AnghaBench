#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pismo_mem {int type; scalar_t__ width; int size; int /*<<< orphan*/  access; int /*<<< orphan*/  base; } ;
struct pismo_data {TYPE_1__* client; } ;
struct pismo_cs_block {int type; int /*<<< orphan*/  device; int /*<<< orphan*/  width; int /*<<< orphan*/  size; int /*<<< orphan*/  access; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pismo_add_nor (struct pismo_data*,int,struct pismo_mem*) ; 
 int /*<<< orphan*/  pismo_add_sram (struct pismo_data*,int,struct pismo_mem*) ; 
 scalar_t__ pismo_width_to_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pismo_add_one(struct pismo_data *pismo, int i,
			  const struct pismo_cs_block *cs, phys_addr_t base)
{
	struct device *dev = &pismo->client->dev;
	struct pismo_mem region;

	region.base = base;
	region.type = cs->type;
	region.width = pismo_width_to_bytes(cs->width);
	region.access = le16_to_cpu(cs->access);
	region.size = le32_to_cpu(cs->size);

	if (region.width == 0) {
		dev_err(dev, "cs%u: bad width: %02x, ignoring\n", i, cs->width);
		return;
	}

	/*
	 * FIXME: may need to the platforms memory controller here, but at
	 * the moment we assume that it has already been correctly setup.
	 * The memory controller can also tell us the base address as well.
	 */

	dev_info(dev, "cs%u: %.32s: type %02x access %u00ps size %uK\n",
		i, cs->device, region.type, region.access, region.size / 1024);

	switch (region.type) {
	case 0:
		break;
	case 1:
		/* static DOC */
		break;
	case 2:
		/* static NOR */
		pismo_add_nor(pismo, i, &region);
		break;
	case 3:
		/* static RAM */
		pismo_add_sram(pismo, i, &region);
		break;
	}
}