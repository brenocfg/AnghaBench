#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {void* maxY; void* minY; void* maxC; void* minC; } ;
struct TYPE_20__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_19__ {void* coef3; void* coef2; void* coef1; void* coef0; int /*<<< orphan*/  dgain; } ;
struct TYPE_18__ {int /*<<< orphan*/  red; int /*<<< orphan*/  green; int /*<<< orphan*/  blue; } ;
struct TYPE_17__ {int couplet_mode_en; int /*<<< orphan*/ * detect_correct; } ;
struct TYPE_16__ {int /*<<< orphan*/  table; int /*<<< orphan*/  spread; } ;
struct TYPE_15__ {int /*<<< orphan*/  table; } ;
struct TYPE_14__ {scalar_t__ hypf_en; int /*<<< orphan*/  thres; int /*<<< orphan*/  gain; } ;
struct TYPE_13__ {int /*<<< orphan*/  gradthrs_vert; int /*<<< orphan*/  gradthrs_horz; int /*<<< orphan*/  table; int /*<<< orphan*/  format; } ;
struct prev_params {int contrast; int brightness; int features; TYPE_10__ yclimit; int /*<<< orphan*/  csc; int /*<<< orphan*/  rgb2rgb; TYPE_9__ blkadj; TYPE_8__ wbal; TYPE_7__ gamma; TYPE_6__ dcor; TYPE_5__ nf; TYPE_4__ luma; TYPE_3__ csup; TYPE_2__ cfa; scalar_t__ update; scalar_t__ busy; } ;
struct TYPE_12__ {struct prev_params* params; int /*<<< orphan*/  active; int /*<<< orphan*/  lock; } ;
struct isp_prev_device {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_DETECT_CORRECT_VAL ; 
 int /*<<< orphan*/  FLR_BLKADJ_BLUE ; 
 int /*<<< orphan*/  FLR_BLKADJ_GREEN ; 
 int /*<<< orphan*/  FLR_BLKADJ_RED ; 
 int /*<<< orphan*/  FLR_CFA_GRADTHRS_HORZ ; 
 int /*<<< orphan*/  FLR_CFA_GRADTHRS_VERT ; 
 int /*<<< orphan*/  FLR_CSUP_GAIN ; 
 int /*<<< orphan*/  FLR_CSUP_THRES ; 
 int /*<<< orphan*/  FLR_NF_STRGTH ; 
 void* FLR_WBAL_COEF ; 
 int /*<<< orphan*/  FLR_WBAL_DGAIN ; 
 int ISPPRV_BRIGHT_DEF ; 
 int ISPPRV_BRIGHT_UNITS ; 
 int ISPPRV_CONTRAST_DEF ; 
 int ISPPRV_CONTRAST_UNITS ; 
 void* ISPPRV_YC_MAX ; 
 void* ISPPRV_YC_MIN ; 
 int /*<<< orphan*/  OMAP3ISP_CFAFMT_BAYER ; 
 int OMAP3ISP_PREV_BLKADJ ; 
 int OMAP3ISP_PREV_BRIGHTNESS ; 
 int OMAP3ISP_PREV_CFA ; 
 int OMAP3ISP_PREV_COLOR_CONV ; 
 int OMAP3ISP_PREV_CONTRAST ; 
 int OMAP3ISP_PREV_DEFECT_COR ; 
 unsigned int OMAP3ISP_PREV_DETECT_CORRECT_CHANNELS ; 
 scalar_t__ OMAP3ISP_PREV_FEATURES_END ; 
 int OMAP3ISP_PREV_GAMMA ; 
 int OMAP3ISP_PREV_NF ; 
 int OMAP3ISP_PREV_RGB2RGB ; 
 int OMAP3ISP_PREV_WB ; 
 int OMAP3ISP_PREV_YC_LIMIT ; 
 int /*<<< orphan*/  cfa_coef_table ; 
 int /*<<< orphan*/  flr_prev_csc ; 
 int /*<<< orphan*/  flr_rgb2rgb ; 
 int /*<<< orphan*/  gamma_table ; 
 int /*<<< orphan*/  luma_enhance_table ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noise_filter_table ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void preview_init_params(struct isp_prev_device *prev)
{
	struct prev_params *params;
	unsigned int i;

	spin_lock_init(&prev->params.lock);

	prev->params.active = ~0;
	prev->params.params[0].busy = 0;
	prev->params.params[0].update = OMAP3ISP_PREV_FEATURES_END - 1;
	prev->params.params[1].busy = 0;
	prev->params.params[1].update = 0;

	params = &prev->params.params[0];

	/* Init values */
	params->contrast = ISPPRV_CONTRAST_DEF * ISPPRV_CONTRAST_UNITS;
	params->brightness = ISPPRV_BRIGHT_DEF * ISPPRV_BRIGHT_UNITS;
	params->cfa.format = OMAP3ISP_CFAFMT_BAYER;
	memcpy(params->cfa.table, cfa_coef_table,
	       sizeof(params->cfa.table));
	params->cfa.gradthrs_horz = FLR_CFA_GRADTHRS_HORZ;
	params->cfa.gradthrs_vert = FLR_CFA_GRADTHRS_VERT;
	params->csup.gain = FLR_CSUP_GAIN;
	params->csup.thres = FLR_CSUP_THRES;
	params->csup.hypf_en = 0;
	memcpy(params->luma.table, luma_enhance_table,
	       sizeof(params->luma.table));
	params->nf.spread = FLR_NF_STRGTH;
	memcpy(params->nf.table, noise_filter_table, sizeof(params->nf.table));
	params->dcor.couplet_mode_en = 1;
	for (i = 0; i < OMAP3ISP_PREV_DETECT_CORRECT_CHANNELS; i++)
		params->dcor.detect_correct[i] = DEF_DETECT_CORRECT_VAL;
	memcpy(params->gamma.blue, gamma_table, sizeof(params->gamma.blue));
	memcpy(params->gamma.green, gamma_table, sizeof(params->gamma.green));
	memcpy(params->gamma.red, gamma_table, sizeof(params->gamma.red));
	params->wbal.dgain = FLR_WBAL_DGAIN;
	params->wbal.coef0 = FLR_WBAL_COEF;
	params->wbal.coef1 = FLR_WBAL_COEF;
	params->wbal.coef2 = FLR_WBAL_COEF;
	params->wbal.coef3 = FLR_WBAL_COEF;
	params->blkadj.red = FLR_BLKADJ_RED;
	params->blkadj.green = FLR_BLKADJ_GREEN;
	params->blkadj.blue = FLR_BLKADJ_BLUE;
	params->rgb2rgb = flr_rgb2rgb;
	params->csc = flr_prev_csc;
	params->yclimit.minC = ISPPRV_YC_MIN;
	params->yclimit.maxC = ISPPRV_YC_MAX;
	params->yclimit.minY = ISPPRV_YC_MIN;
	params->yclimit.maxY = ISPPRV_YC_MAX;

	params->features = OMAP3ISP_PREV_CFA | OMAP3ISP_PREV_DEFECT_COR
			 | OMAP3ISP_PREV_NF | OMAP3ISP_PREV_GAMMA
			 | OMAP3ISP_PREV_BLKADJ | OMAP3ISP_PREV_YC_LIMIT
			 | OMAP3ISP_PREV_RGB2RGB | OMAP3ISP_PREV_COLOR_CONV
			 | OMAP3ISP_PREV_WB | OMAP3ISP_PREV_BRIGHTNESS
			 | OMAP3ISP_PREV_CONTRAST;
}