#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ dir; } ;
struct TYPE_7__ {int nbytes; } ;
struct TYPE_10__ {TYPE_3__ data; TYPE_2__ addr; } ;
struct spi_mem_dirmap_info {TYPE_5__ op_tmpl; } ;
struct spi_mem_dirmap_desc {int nodirmap; struct spi_mem_dirmap_info info; struct spi_mem* mem; } ;
struct spi_mem {TYPE_1__* spi; } ;
struct spi_controller {TYPE_4__* mem_ops; } ;
struct TYPE_9__ {int (* dirmap_create ) (struct spi_mem_dirmap_desc*) ;} ;
struct TYPE_6__ {struct spi_controller* controller; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 struct spi_mem_dirmap_desc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SPI_MEM_NO_DATA ; 
 int /*<<< orphan*/  kfree (struct spi_mem_dirmap_desc*) ; 
 struct spi_mem_dirmap_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_mem_supports_op (struct spi_mem*,TYPE_5__*) ; 
 int stub1 (struct spi_mem_dirmap_desc*) ; 

struct spi_mem_dirmap_desc *
spi_mem_dirmap_create(struct spi_mem *mem,
		      const struct spi_mem_dirmap_info *info)
{
	struct spi_controller *ctlr = mem->spi->controller;
	struct spi_mem_dirmap_desc *desc;
	int ret = -ENOTSUPP;

	/* Make sure the number of address cycles is between 1 and 8 bytes. */
	if (!info->op_tmpl.addr.nbytes || info->op_tmpl.addr.nbytes > 8)
		return ERR_PTR(-EINVAL);

	/* data.dir should either be SPI_MEM_DATA_IN or SPI_MEM_DATA_OUT. */
	if (info->op_tmpl.data.dir == SPI_MEM_NO_DATA)
		return ERR_PTR(-EINVAL);

	desc = kzalloc(sizeof(*desc), GFP_KERNEL);
	if (!desc)
		return ERR_PTR(-ENOMEM);

	desc->mem = mem;
	desc->info = *info;
	if (ctlr->mem_ops && ctlr->mem_ops->dirmap_create)
		ret = ctlr->mem_ops->dirmap_create(desc);

	if (ret) {
		desc->nodirmap = true;
		if (!spi_mem_supports_op(desc->mem, &desc->info.op_tmpl))
			ret = -ENOTSUPP;
		else
			ret = 0;
	}

	if (ret) {
		kfree(desc);
		return ERR_PTR(ret);
	}

	return desc;
}