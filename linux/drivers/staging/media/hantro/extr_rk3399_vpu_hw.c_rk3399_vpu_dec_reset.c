#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hantro_dev {int dummy; } ;
struct hantro_ctx {struct hantro_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDPU_REG_EN_FLAGS ; 
 int /*<<< orphan*/  VDPU_REG_INTERRUPT ; 
 int VDPU_REG_INTERRUPT_DEC_IRQ_DIS ; 
 int /*<<< orphan*/  VDPU_REG_SOFT_RESET ; 
 int /*<<< orphan*/  vdpu_write (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk3399_vpu_dec_reset(struct hantro_ctx *ctx)
{
	struct hantro_dev *vpu = ctx->dev;

	vdpu_write(vpu, VDPU_REG_INTERRUPT_DEC_IRQ_DIS, VDPU_REG_INTERRUPT);
	vdpu_write(vpu, 0, VDPU_REG_EN_FLAGS);
	vdpu_write(vpu, 1, VDPU_REG_SOFT_RESET);
}