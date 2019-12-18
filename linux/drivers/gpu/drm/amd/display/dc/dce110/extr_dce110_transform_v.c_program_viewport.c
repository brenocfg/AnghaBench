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
typedef  scalar_t__ uint32_t ;
struct rect {int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_2__ {struct dc_context* ctx; } ;
struct dce_transform {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCLV_VIEWPORT_SIZE ; 
 int /*<<< orphan*/  SCLV_VIEWPORT_SIZE_C ; 
 int /*<<< orphan*/  SCLV_VIEWPORT_START ; 
 int /*<<< orphan*/  SCLV_VIEWPORT_START_C ; 
 int /*<<< orphan*/  VIEWPORT_HEIGHT ; 
 int /*<<< orphan*/  VIEWPORT_HEIGHT_C ; 
 int /*<<< orphan*/  VIEWPORT_WIDTH ; 
 int /*<<< orphan*/  VIEWPORT_WIDTH_C ; 
 int /*<<< orphan*/  VIEWPORT_X_START ; 
 int /*<<< orphan*/  VIEWPORT_X_START_C ; 
 int /*<<< orphan*/  VIEWPORT_Y_START ; 
 int /*<<< orphan*/  VIEWPORT_Y_START_C ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,scalar_t__,scalar_t__) ; 
 scalar_t__ mmSCLV_VIEWPORT_SIZE ; 
 scalar_t__ mmSCLV_VIEWPORT_SIZE_C ; 
 scalar_t__ mmSCLV_VIEWPORT_START ; 
 scalar_t__ mmSCLV_VIEWPORT_START_C ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_viewport(
	struct dce_transform *xfm_dce,
	struct rect *luma_view_port,
	struct rect *chroma_view_port)
{
	struct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t value = 0;
	uint32_t addr = 0;

	if (luma_view_port->width != 0 && luma_view_port->height != 0) {
		addr = mmSCLV_VIEWPORT_START;
		value = 0;
		set_reg_field_value(
			value,
			luma_view_port->x,
			SCLV_VIEWPORT_START,
			VIEWPORT_X_START);
		set_reg_field_value(
			value,
			luma_view_port->y,
			SCLV_VIEWPORT_START,
			VIEWPORT_Y_START);
		dm_write_reg(ctx, addr, value);

		addr = mmSCLV_VIEWPORT_SIZE;
		value = 0;
		set_reg_field_value(
			value,
			luma_view_port->height,
			SCLV_VIEWPORT_SIZE,
			VIEWPORT_HEIGHT);
		set_reg_field_value(
			value,
			luma_view_port->width,
			SCLV_VIEWPORT_SIZE,
			VIEWPORT_WIDTH);
		dm_write_reg(ctx, addr, value);
	}

	if (chroma_view_port->width != 0 && chroma_view_port->height != 0) {
		addr = mmSCLV_VIEWPORT_START_C;
		value = 0;
		set_reg_field_value(
			value,
			chroma_view_port->x,
			SCLV_VIEWPORT_START_C,
			VIEWPORT_X_START_C);
		set_reg_field_value(
			value,
			chroma_view_port->y,
			SCLV_VIEWPORT_START_C,
			VIEWPORT_Y_START_C);
		dm_write_reg(ctx, addr, value);

		addr = mmSCLV_VIEWPORT_SIZE_C;
		value = 0;
		set_reg_field_value(
			value,
			chroma_view_port->height,
			SCLV_VIEWPORT_SIZE_C,
			VIEWPORT_HEIGHT_C);
		set_reg_field_value(
			value,
			chroma_view_port->width,
			SCLV_VIEWPORT_SIZE_C,
			VIEWPORT_WIDTH_C);
		dm_write_reg(ctx, addr, value);
	}
}