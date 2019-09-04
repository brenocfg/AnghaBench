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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct isc_ctrls {int r_gain; int b_gain; size_t gamma_index; int brightness; int contrast; } ;
struct isc_device {int /*<<< orphan*/ * pipeline; TYPE_1__* raw_fmt; struct isc_ctrls ctrls; struct regmap* regmap; } ;
struct fmt_config {int cfa_baycfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  GAMMA_ENTRIES ; 
 int /*<<< orphan*/  ISC_CBC_BRIGHT ; 
 int /*<<< orphan*/  ISC_CBC_CONTRAST ; 
 int /*<<< orphan*/  ISC_CFA_CFG ; 
 int ISC_CFA_CFG_EITPOL ; 
 int /*<<< orphan*/  ISC_CSC_CBB_OCB ; 
 int /*<<< orphan*/  ISC_CSC_CBR_CBG ; 
 int /*<<< orphan*/  ISC_CSC_CRB_OCR ; 
 int /*<<< orphan*/  ISC_CSC_CRR_CRG ; 
 int /*<<< orphan*/  ISC_CSC_YB_OY ; 
 int /*<<< orphan*/  ISC_CSC_YR_YG ; 
 int /*<<< orphan*/  ISC_GAM_BENTRY ; 
 int /*<<< orphan*/  ISC_GAM_GENTRY ; 
 int /*<<< orphan*/  ISC_GAM_RENTRY ; 
 unsigned int ISC_PIPE_LINE_NODE_NUM ; 
 int /*<<< orphan*/  ISC_WB_CFG ; 
 int /*<<< orphan*/  ISC_WB_G_BGR ; 
 int /*<<< orphan*/  ISC_WB_G_RGR ; 
 int /*<<< orphan*/  ISC_WB_O_BGR ; 
 int /*<<< orphan*/  ISC_WB_O_RGR ; 
 struct fmt_config* get_fmt_config (int /*<<< orphan*/ ) ; 
 int** isc_gamma_table ; 
 int /*<<< orphan*/  regmap_bulk_write (struct regmap*,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isc_set_pipeline(struct isc_device *isc, u32 pipeline)
{
	struct regmap *regmap = isc->regmap;
	struct isc_ctrls *ctrls = &isc->ctrls;
	struct fmt_config *config = get_fmt_config(isc->raw_fmt->fourcc);
	u32 val, bay_cfg;
	const u32 *gamma;
	unsigned int i;

	/* WB-->CFA-->CC-->GAM-->CSC-->CBC-->SUB422-->SUB420 */
	for (i = 0; i < ISC_PIPE_LINE_NODE_NUM; i++) {
		val = pipeline & BIT(i) ? 1 : 0;
		regmap_field_write(isc->pipeline[i], val);
	}

	if (!pipeline)
		return;

	bay_cfg = config->cfa_baycfg;

	regmap_write(regmap, ISC_WB_CFG, bay_cfg);
	regmap_write(regmap, ISC_WB_O_RGR, 0x0);
	regmap_write(regmap, ISC_WB_O_BGR, 0x0);
	regmap_write(regmap, ISC_WB_G_RGR, ctrls->r_gain | (0x1 << 25));
	regmap_write(regmap, ISC_WB_G_BGR, ctrls->b_gain | (0x1 << 25));

	regmap_write(regmap, ISC_CFA_CFG, bay_cfg | ISC_CFA_CFG_EITPOL);

	gamma = &isc_gamma_table[ctrls->gamma_index][0];
	regmap_bulk_write(regmap, ISC_GAM_BENTRY, gamma, GAMMA_ENTRIES);
	regmap_bulk_write(regmap, ISC_GAM_GENTRY, gamma, GAMMA_ENTRIES);
	regmap_bulk_write(regmap, ISC_GAM_RENTRY, gamma, GAMMA_ENTRIES);

	/* Convert RGB to YUV */
	regmap_write(regmap, ISC_CSC_YR_YG, 0x42 | (0x81 << 16));
	regmap_write(regmap, ISC_CSC_YB_OY, 0x19 | (0x10 << 16));
	regmap_write(regmap, ISC_CSC_CBR_CBG, 0xFDA | (0xFB6 << 16));
	regmap_write(regmap, ISC_CSC_CBB_OCB, 0x70 | (0x80 << 16));
	regmap_write(regmap, ISC_CSC_CRR_CRG, 0x70 | (0xFA2 << 16));
	regmap_write(regmap, ISC_CSC_CRB_OCR, 0xFEE | (0x80 << 16));

	regmap_write(regmap, ISC_CBC_BRIGHT, ctrls->brightness);
	regmap_write(regmap, ISC_CBC_CONTRAST, ctrls->contrast);
}