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
typedef  scalar_t__ u64 ;
struct TYPE_5__ {void* in; } ;
struct TYPE_6__ {size_t nbytes; TYPE_1__ buf; } ;
struct TYPE_7__ {scalar_t__ val; } ;
struct spi_mem_op {TYPE_2__ data; TYPE_3__ addr; } ;
struct TYPE_8__ {scalar_t__ offset; struct spi_mem_op op_tmpl; } ;
struct spi_mem_dirmap_desc {int /*<<< orphan*/  mem; TYPE_4__ info; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int spi_mem_adjust_op_size (int /*<<< orphan*/ ,struct spi_mem_op*) ; 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 

__attribute__((used)) static ssize_t spi_mem_no_dirmap_read(struct spi_mem_dirmap_desc *desc,
				      u64 offs, size_t len, void *buf)
{
	struct spi_mem_op op = desc->info.op_tmpl;
	int ret;

	op.addr.val = desc->info.offset + offs;
	op.data.buf.in = buf;
	op.data.nbytes = len;
	ret = spi_mem_adjust_op_size(desc->mem, &op);
	if (ret)
		return ret;

	ret = spi_mem_exec_op(desc->mem, &op);
	if (ret)
		return ret;

	return op.data.nbytes;
}