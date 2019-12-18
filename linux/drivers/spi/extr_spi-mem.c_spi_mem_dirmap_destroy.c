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
struct spi_mem_dirmap_desc {int /*<<< orphan*/  nodirmap; TYPE_2__* mem; } ;
struct spi_controller {TYPE_3__* mem_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* dirmap_destroy ) (struct spi_mem_dirmap_desc*) ;} ;
struct TYPE_5__ {TYPE_1__* spi; } ;
struct TYPE_4__ {struct spi_controller* controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct spi_mem_dirmap_desc*) ; 
 int /*<<< orphan*/  stub1 (struct spi_mem_dirmap_desc*) ; 

void spi_mem_dirmap_destroy(struct spi_mem_dirmap_desc *desc)
{
	struct spi_controller *ctlr = desc->mem->spi->controller;

	if (!desc->nodirmap && ctlr->mem_ops && ctlr->mem_ops->dirmap_destroy)
		ctlr->mem_ops->dirmap_destroy(desc);

	kfree(desc);
}