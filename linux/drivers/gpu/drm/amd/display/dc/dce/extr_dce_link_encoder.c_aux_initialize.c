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
struct TYPE_2__ {int hpd_source; struct dc_context* ctx; } ;
struct dce110_link_encoder {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;
typedef  enum hpd_source_id { ____Placeholder_hpd_source_id } hpd_source_id ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_CONTROL ; 
 int /*<<< orphan*/  AUX_DPHY_RX_CONTROL0 ; 
 int /*<<< orphan*/  AUX_HPD_SEL ; 
 int /*<<< orphan*/  AUX_LS_READ_EN ; 
 int /*<<< orphan*/  AUX_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUX_RX_RECEIVE_WINDOW ; 
 int /*<<< orphan*/  dm_read_reg (struct dc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aux_initialize(
	struct dce110_link_encoder *enc110)
{
	struct dc_context *ctx = enc110->base.ctx;
	enum hpd_source_id hpd_source = enc110->base.hpd_source;
	uint32_t addr = AUX_REG(AUX_CONTROL);
	uint32_t value = dm_read_reg(ctx, addr);

	set_reg_field_value(value, hpd_source, AUX_CONTROL, AUX_HPD_SEL);
	set_reg_field_value(value, 0, AUX_CONTROL, AUX_LS_READ_EN);
	dm_write_reg(ctx, addr, value);

	addr = AUX_REG(AUX_DPHY_RX_CONTROL0);
	value = dm_read_reg(ctx, addr);

	/* 1/4 window (the maximum allowed) */
	set_reg_field_value(value, 1,
			AUX_DPHY_RX_CONTROL0, AUX_RX_RECEIVE_WINDOW);
	dm_write_reg(ctx, addr, value);

}