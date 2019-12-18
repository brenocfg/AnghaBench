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
struct TYPE_4__ {void* in; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; TYPE_1__ buf; } ;
struct TYPE_6__ {TYPE_2__ data; } ;
struct nand_op_instr {scalar_t__ type; TYPE_3__ ctx; } ;

/* Variables and functions */
 scalar_t__ NAND_OP_DATA_IN_INSTR ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
meson_nand_op_put_dma_safe_input_buf(const struct nand_op_instr *instr,
				     void *buf)
{
	if (WARN_ON(instr->type != NAND_OP_DATA_IN_INSTR) ||
	    WARN_ON(!buf))
		return;

	if (buf == instr->ctx.data.buf.in)
		return;

	memcpy(instr->ctx.data.buf.in, buf, instr->ctx.data.len);
	kfree(buf);
}