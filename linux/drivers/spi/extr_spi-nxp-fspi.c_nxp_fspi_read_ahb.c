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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ val; } ;
struct TYPE_4__ {int /*<<< orphan*/  in; } ;
struct TYPE_5__ {TYPE_1__ buf; int /*<<< orphan*/  nbytes; } ;
struct spi_mem_op {TYPE_3__ addr; TYPE_2__ data; } ;
struct nxp_fspi {scalar_t__ ahb_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nxp_fspi_read_ahb(struct nxp_fspi *f, const struct spi_mem_op *op)
{
	u32 len = op->data.nbytes;

	/* Read out the data directly from the AHB buffer. */
	memcpy_fromio(op->data.buf.in, (f->ahb_addr + op->addr.val), len);
}