#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {scalar_t__ dir; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
struct TYPE_10__ {TYPE_2__ op_tmpl; } ;
struct spi_mem_dirmap_desc {TYPE_6__* mem; scalar_t__ nodirmap; TYPE_3__ info; } ;
struct spi_controller {TYPE_4__* mem_ops; } ;
typedef  int ssize_t ;
struct TYPE_13__ {TYPE_5__* spi; } ;
struct TYPE_12__ {struct spi_controller* controller; } ;
struct TYPE_11__ {int (* dirmap_write ) (struct spi_mem_dirmap_desc*,int /*<<< orphan*/ ,size_t,void const*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ SPI_MEM_DATA_OUT ; 
 int /*<<< orphan*/  spi_mem_access_end (TYPE_6__*) ; 
 int spi_mem_access_start (TYPE_6__*) ; 
 int spi_mem_no_dirmap_write (struct spi_mem_dirmap_desc*,int /*<<< orphan*/ ,size_t,void const*) ; 
 int stub1 (struct spi_mem_dirmap_desc*,int /*<<< orphan*/ ,size_t,void const*) ; 

ssize_t spi_mem_dirmap_write(struct spi_mem_dirmap_desc *desc,
			     u64 offs, size_t len, const void *buf)
{
	struct spi_controller *ctlr = desc->mem->spi->controller;
	ssize_t ret;

	if (desc->info.op_tmpl.data.dir != SPI_MEM_DATA_OUT)
		return -EINVAL;

	if (!len)
		return 0;

	if (desc->nodirmap) {
		ret = spi_mem_no_dirmap_write(desc, offs, len, buf);
	} else if (ctlr->mem_ops && ctlr->mem_ops->dirmap_write) {
		ret = spi_mem_access_start(desc->mem);
		if (ret)
			return ret;

		ret = ctlr->mem_ops->dirmap_write(desc, offs, len, buf);

		spi_mem_access_end(desc->mem);
	} else {
		ret = -ENOTSUPP;
	}

	return ret;
}