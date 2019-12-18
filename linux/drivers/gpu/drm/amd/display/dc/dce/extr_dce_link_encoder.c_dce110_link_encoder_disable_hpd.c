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
typedef  int /*<<< orphan*/  uint32_t ;
struct link_encoder {int dummy; } ;
struct TYPE_2__ {struct dc_context* ctx; } ;
struct dce110_link_encoder {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_HPD_CONTROL ; 
 int /*<<< orphan*/  DC_HPD_EN ; 
 int /*<<< orphan*/  HPD_REG (int /*<<< orphan*/ ) ; 
 struct dce110_link_encoder* TO_DCE110_LINK_ENC (struct link_encoder*) ; 
 int /*<<< orphan*/  dm_read_reg (struct dc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_link_encoder_disable_hpd(struct link_encoder *enc)
{
	struct dce110_link_encoder *enc110 = TO_DCE110_LINK_ENC(enc);
	struct dc_context *ctx = enc110->base.ctx;
	uint32_t addr = HPD_REG(DC_HPD_CONTROL);
	uint32_t value = dm_read_reg(ctx, addr);

	set_reg_field_value(value, 0, DC_HPD_CONTROL, DC_HPD_EN);
}