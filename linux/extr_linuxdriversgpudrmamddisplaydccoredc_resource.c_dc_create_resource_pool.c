#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource_pool {int /*<<< orphan*/  ref_clock_inKhz; } ;
struct hw_asic_id {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  crystal_frequency; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct dc_firmware_info {TYPE_4__ pll_info; TYPE_1__ member_0; } ;
struct dc {TYPE_3__* ctx; } ;
typedef  enum dce_version { ____Placeholder_dce_version } dce_version ;
struct TYPE_10__ {TYPE_2__* funcs; } ;
struct TYPE_8__ {TYPE_5__* dc_bios; } ;
struct TYPE_7__ {scalar_t__ (* get_firmware_info ) (TYPE_5__*,struct dc_firmware_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 scalar_t__ BP_RESULT_OK ; 
#define  DCE_VERSION_10_0 135 
#define  DCE_VERSION_11_0 134 
#define  DCE_VERSION_11_2 133 
#define  DCE_VERSION_11_22 132 
#define  DCE_VERSION_12_0 131 
#define  DCE_VERSION_8_0 130 
#define  DCE_VERSION_8_1 129 
#define  DCE_VERSION_8_3 128 
 struct resource_pool* dce100_create_resource_pool (int,struct dc*) ; 
 struct resource_pool* dce110_create_resource_pool (int,struct dc*,struct hw_asic_id) ; 
 struct resource_pool* dce112_create_resource_pool (int,struct dc*) ; 
 struct resource_pool* dce120_create_resource_pool (int,struct dc*) ; 
 struct resource_pool* dce80_create_resource_pool (int,struct dc*) ; 
 struct resource_pool* dce81_create_resource_pool (int,struct dc*) ; 
 struct resource_pool* dce83_create_resource_pool (int,struct dc*) ; 
 scalar_t__ stub1 (TYPE_5__*,struct dc_firmware_info*) ; 

struct resource_pool *dc_create_resource_pool(
				struct dc  *dc,
				int num_virtual_links,
				enum dce_version dc_version,
				struct hw_asic_id asic_id)
{
	struct resource_pool *res_pool = NULL;

	switch (dc_version) {
	case DCE_VERSION_8_0:
		res_pool = dce80_create_resource_pool(
			num_virtual_links, dc);
		break;
	case DCE_VERSION_8_1:
		res_pool = dce81_create_resource_pool(
			num_virtual_links, dc);
		break;
	case DCE_VERSION_8_3:
		res_pool = dce83_create_resource_pool(
			num_virtual_links, dc);
		break;
	case DCE_VERSION_10_0:
		res_pool = dce100_create_resource_pool(
				num_virtual_links, dc);
		break;
	case DCE_VERSION_11_0:
		res_pool = dce110_create_resource_pool(
			num_virtual_links, dc, asic_id);
		break;
	case DCE_VERSION_11_2:
	case DCE_VERSION_11_22:
		res_pool = dce112_create_resource_pool(
			num_virtual_links, dc);
		break;
	case DCE_VERSION_12_0:
		res_pool = dce120_create_resource_pool(
			num_virtual_links, dc);
		break;

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case DCN_VERSION_1_0:
		res_pool = dcn10_create_resource_pool(
				num_virtual_links, dc);
		break;
#endif


	default:
		break;
	}
	if (res_pool != NULL) {
		struct dc_firmware_info fw_info = { { 0 } };

		if (dc->ctx->dc_bios->funcs->get_firmware_info(
				dc->ctx->dc_bios, &fw_info) == BP_RESULT_OK) {
				res_pool->ref_clock_inKhz = fw_info.pll_info.crystal_frequency;
			} else
				ASSERT_CRITICAL(false);
	}

	return res_pool;
}