#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_device {struct ast_private* dev_private; TYPE_2__* pdev; } ;
struct device_node {int dummy; } ;
struct ast_private {int config_mode; int dram_bus_width; scalar_t__ chip; int mclk; void* dram_type; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ AST2300 ; 
 scalar_t__ AST2400 ; 
 scalar_t__ AST2500 ; 
 void* AST_DRAM_1Gx16 ; 
 void* AST_DRAM_1Gx32 ; 
 void* AST_DRAM_2Gx16 ; 
 void* AST_DRAM_4Gx16 ; 
 void* AST_DRAM_512Mx16 ; 
 void* AST_DRAM_512Mx32 ; 
 void* AST_DRAM_8Gx16 ; 
 int ast_read32 (struct ast_private*,int) ; 
#define  ast_use_defaults 130 
#define  ast_use_dt 129 
#define  ast_use_p2a 128 
 int /*<<< orphan*/  ast_write32 (struct ast_private*,int,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int ast_get_dram_info(struct drm_device *dev)
{
	struct device_node *np = dev->pdev->dev.of_node;
	struct ast_private *ast = dev->dev_private;
	uint32_t mcr_cfg, mcr_scu_mpll, mcr_scu_strap;
	uint32_t denum, num, div, ref_pll, dsel;

	switch (ast->config_mode) {
	case ast_use_dt:
		/*
		 * If some properties are missing, use reasonable
		 * defaults for AST2400
		 */
		if (of_property_read_u32(np, "aspeed,mcr-configuration",
					 &mcr_cfg))
			mcr_cfg = 0x00000577;
		if (of_property_read_u32(np, "aspeed,mcr-scu-mpll",
					 &mcr_scu_mpll))
			mcr_scu_mpll = 0x000050C0;
		if (of_property_read_u32(np, "aspeed,mcr-scu-strap",
					 &mcr_scu_strap))
			mcr_scu_strap = 0;
		break;
	case ast_use_p2a:
		ast_write32(ast, 0xf004, 0x1e6e0000);
		ast_write32(ast, 0xf000, 0x1);
		mcr_cfg = ast_read32(ast, 0x10004);
		mcr_scu_mpll = ast_read32(ast, 0x10120);
		mcr_scu_strap = ast_read32(ast, 0x10170);
		break;
	case ast_use_defaults:
	default:
		ast->dram_bus_width = 16;
		ast->dram_type = AST_DRAM_1Gx16;
		if (ast->chip == AST2500)
			ast->mclk = 800;
		else
			ast->mclk = 396;
		return 0;
	}

	if (mcr_cfg & 0x40)
		ast->dram_bus_width = 16;
	else
		ast->dram_bus_width = 32;

	if (ast->chip == AST2500) {
		switch (mcr_cfg & 0x03) {
		case 0:
			ast->dram_type = AST_DRAM_1Gx16;
			break;
		default:
		case 1:
			ast->dram_type = AST_DRAM_2Gx16;
			break;
		case 2:
			ast->dram_type = AST_DRAM_4Gx16;
			break;
		case 3:
			ast->dram_type = AST_DRAM_8Gx16;
			break;
		}
	} else if (ast->chip == AST2300 || ast->chip == AST2400) {
		switch (mcr_cfg & 0x03) {
		case 0:
			ast->dram_type = AST_DRAM_512Mx16;
			break;
		default:
		case 1:
			ast->dram_type = AST_DRAM_1Gx16;
			break;
		case 2:
			ast->dram_type = AST_DRAM_2Gx16;
			break;
		case 3:
			ast->dram_type = AST_DRAM_4Gx16;
			break;
		}
	} else {
		switch (mcr_cfg & 0x0c) {
		case 0:
		case 4:
			ast->dram_type = AST_DRAM_512Mx16;
			break;
		case 8:
			if (mcr_cfg & 0x40)
				ast->dram_type = AST_DRAM_1Gx16;
			else
				ast->dram_type = AST_DRAM_512Mx32;
			break;
		case 0xc:
			ast->dram_type = AST_DRAM_1Gx32;
			break;
		}
	}

	if (mcr_scu_strap & 0x2000)
		ref_pll = 14318;
	else
		ref_pll = 12000;

	denum = mcr_scu_mpll & 0x1f;
	num = (mcr_scu_mpll & 0x3fe0) >> 5;
	dsel = (mcr_scu_mpll & 0xc000) >> 14;
	switch (dsel) {
	case 3:
		div = 0x4;
		break;
	case 2:
	case 1:
		div = 0x2;
		break;
	default:
		div = 0x1;
		break;
	}
	ast->mclk = ref_pll * (num + 2) / ((denum + 2) * (div * 1000));
	return 0;
}