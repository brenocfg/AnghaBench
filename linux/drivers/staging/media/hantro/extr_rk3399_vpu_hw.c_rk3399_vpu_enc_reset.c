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
 int /*<<< orphan*/  VEPU_REG_AXI_CTRL ; 
 int /*<<< orphan*/  VEPU_REG_ENCODE_START ; 
 int /*<<< orphan*/  VEPU_REG_INTERRUPT ; 
 int /*<<< orphan*/  VEPU_REG_INTERRUPT_DIS_BIT ; 
 int /*<<< orphan*/  vepu_write (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk3399_vpu_enc_reset(struct hantro_ctx *ctx)
{
	struct hantro_dev *vpu = ctx->dev;

	vepu_write(vpu, VEPU_REG_INTERRUPT_DIS_BIT, VEPU_REG_INTERRUPT);
	vepu_write(vpu, 0, VEPU_REG_ENCODE_START);
	vepu_write(vpu, 0, VEPU_REG_AXI_CTRL);
}