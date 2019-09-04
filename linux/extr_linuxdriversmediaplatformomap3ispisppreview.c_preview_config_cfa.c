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
struct omap3isp_prev_cfa {int const gradthrs_vert; int const gradthrs_horz; int** table; } ;
struct prev_params {struct omap3isp_prev_cfa cfa; } ;
struct TYPE_2__ {size_t cfa_order; } ;
struct isp_prev_device {TYPE_1__ params; } ;
struct isp_device {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_CFA ; 
 int const ISPPRV_CFA_GRADTH_HOR_SHIFT ; 
 int const ISPPRV_CFA_GRADTH_VER_SHIFT ; 
 int const ISPPRV_CFA_TABLE_ADDR ; 
 int /*<<< orphan*/  ISPPRV_SET_TBL_ADDR ; 
 int /*<<< orphan*/  ISPPRV_SET_TBL_DATA ; 
 unsigned int OMAP3ISP_PREV_CFA_BLK_SIZE ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void preview_config_cfa(struct isp_prev_device *prev,
			       const struct prev_params *params)
{
	static const unsigned int cfa_coef_order[4][4] = {
		{ 0, 1, 2, 3 }, /* GRBG */
		{ 1, 0, 3, 2 }, /* RGGB */
		{ 2, 3, 0, 1 }, /* BGGR */
		{ 3, 2, 1, 0 }, /* GBRG */
	};
	const unsigned int *order = cfa_coef_order[prev->params.cfa_order];
	const struct omap3isp_prev_cfa *cfa = &params->cfa;
	struct isp_device *isp = to_isp_device(prev);
	unsigned int i;
	unsigned int j;

	isp_reg_writel(isp,
		(cfa->gradthrs_vert << ISPPRV_CFA_GRADTH_VER_SHIFT) |
		(cfa->gradthrs_horz << ISPPRV_CFA_GRADTH_HOR_SHIFT),
		OMAP3_ISP_IOMEM_PREV, ISPPRV_CFA);

	isp_reg_writel(isp, ISPPRV_CFA_TABLE_ADDR,
		       OMAP3_ISP_IOMEM_PREV, ISPPRV_SET_TBL_ADDR);

	for (i = 0; i < 4; ++i) {
		const __u32 *block = cfa->table[order[i]];

		for (j = 0; j < OMAP3ISP_PREV_CFA_BLK_SIZE; ++j)
			isp_reg_writel(isp, block[j], OMAP3_ISP_IOMEM_PREV,
				       ISPPRV_SET_TBL_DATA);
	}
}