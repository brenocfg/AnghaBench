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
struct TYPE_4__ {scalar_t__ out; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; TYPE_1__ buf; } ;
struct TYPE_5__ {TYPE_3__ data; } ;
struct nand_op_instr {scalar_t__ type; TYPE_2__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NAND_OP_DATA_OUT_INSTR ; 
 scalar_t__ WARN_ON (int) ; 
 void* kmemdup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ meson_nfc_is_buffer_dma_safe (scalar_t__) ; 

__attribute__((used)) static void *
meson_nand_op_get_dma_safe_output_buf(const struct nand_op_instr *instr)
{
	if (WARN_ON(instr->type != NAND_OP_DATA_OUT_INSTR))
		return NULL;

	if (meson_nfc_is_buffer_dma_safe(instr->ctx.data.buf.out))
		return (void *)instr->ctx.data.buf.out;

	return kmemdup(instr->ctx.data.buf.out,
		       instr->ctx.data.len, GFP_KERNEL);
}