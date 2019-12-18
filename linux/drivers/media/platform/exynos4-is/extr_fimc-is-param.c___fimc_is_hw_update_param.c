#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int /*<<< orphan*/  config; int /*<<< orphan*/  dma_input; int /*<<< orphan*/  otf_input; int /*<<< orphan*/  control; } ;
struct TYPE_11__ {int /*<<< orphan*/  otf_output; int /*<<< orphan*/  dma_input; int /*<<< orphan*/  otf_input; int /*<<< orphan*/  control; } ;
struct TYPE_9__ {int /*<<< orphan*/  dma2_output; int /*<<< orphan*/  dma1_output; int /*<<< orphan*/  otf_output; int /*<<< orphan*/  afc; int /*<<< orphan*/  metering; int /*<<< orphan*/  adjust; int /*<<< orphan*/  iso; int /*<<< orphan*/  effect; int /*<<< orphan*/  awb; int /*<<< orphan*/  flash; int /*<<< orphan*/  aa; int /*<<< orphan*/  dma2_input; int /*<<< orphan*/  dma1_input; int /*<<< orphan*/  otf_input; int /*<<< orphan*/  control; } ;
struct is_param_region {TYPE_6__ fd; TYPE_4__ drc; TYPE_2__ isp; } ;
struct fimc_is {size_t config_index; struct chain_config* config; TYPE_1__* is_p_region; } ;
struct TYPE_14__ {int /*<<< orphan*/  config; int /*<<< orphan*/  dma_input; int /*<<< orphan*/  otf_input; int /*<<< orphan*/  control; } ;
struct TYPE_12__ {int /*<<< orphan*/  otf_output; int /*<<< orphan*/  dma_input; int /*<<< orphan*/  otf_input; int /*<<< orphan*/  control; } ;
struct TYPE_10__ {int /*<<< orphan*/  dma2_output; int /*<<< orphan*/  dma1_output; int /*<<< orphan*/  otf_output; int /*<<< orphan*/  afc; int /*<<< orphan*/  metering; int /*<<< orphan*/  adjust; int /*<<< orphan*/  iso; int /*<<< orphan*/  effect; int /*<<< orphan*/  awb; int /*<<< orphan*/  flash; int /*<<< orphan*/  aa; int /*<<< orphan*/  dma2_input; int /*<<< orphan*/  dma1_input; int /*<<< orphan*/  otf_input; int /*<<< orphan*/  control; } ;
struct chain_config {TYPE_7__ fd; TYPE_5__ drc; TYPE_3__ isp; } ;
struct TYPE_8__ {struct is_param_region parameter; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PARAM_DRC_CONTROL 150 
#define  PARAM_DRC_DMA_INPUT 149 
#define  PARAM_DRC_OTF_INPUT 148 
#define  PARAM_DRC_OTF_OUTPUT 147 
#define  PARAM_FD_CONFIG 146 
#define  PARAM_FD_CONTROL 145 
#define  PARAM_FD_DMA_INPUT 144 
#define  PARAM_FD_OTF_INPUT 143 
#define  PARAM_ISP_AA 142 
#define  PARAM_ISP_ADJUST 141 
#define  PARAM_ISP_AFC 140 
#define  PARAM_ISP_AWB 139 
#define  PARAM_ISP_CONTROL 138 
#define  PARAM_ISP_DMA1_INPUT 137 
#define  PARAM_ISP_DMA1_OUTPUT 136 
#define  PARAM_ISP_DMA2_INPUT 135 
#define  PARAM_ISP_DMA2_OUTPUT 134 
#define  PARAM_ISP_FLASH 133 
#define  PARAM_ISP_IMAGE_EFFECT 132 
#define  PARAM_ISP_ISO 131 
#define  PARAM_ISP_METERING 130 
#define  PARAM_ISP_OTF_INPUT 129 
#define  PARAM_ISP_OTF_OUTPUT 128 
 int /*<<< orphan*/  __hw_param_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int __fimc_is_hw_update_param(struct fimc_is *is, u32 offset)
{
	struct is_param_region *par = &is->is_p_region->parameter;
	struct chain_config *cfg = &is->config[is->config_index];

	switch (offset) {
	case PARAM_ISP_CONTROL:
		__hw_param_copy(&par->isp.control, &cfg->isp.control);
		break;

	case PARAM_ISP_OTF_INPUT:
		__hw_param_copy(&par->isp.otf_input, &cfg->isp.otf_input);
		break;

	case PARAM_ISP_DMA1_INPUT:
		__hw_param_copy(&par->isp.dma1_input, &cfg->isp.dma1_input);
		break;

	case PARAM_ISP_DMA2_INPUT:
		__hw_param_copy(&par->isp.dma2_input, &cfg->isp.dma2_input);
		break;

	case PARAM_ISP_AA:
		__hw_param_copy(&par->isp.aa, &cfg->isp.aa);
		break;

	case PARAM_ISP_FLASH:
		__hw_param_copy(&par->isp.flash, &cfg->isp.flash);
		break;

	case PARAM_ISP_AWB:
		__hw_param_copy(&par->isp.awb, &cfg->isp.awb);
		break;

	case PARAM_ISP_IMAGE_EFFECT:
		__hw_param_copy(&par->isp.effect, &cfg->isp.effect);
		break;

	case PARAM_ISP_ISO:
		__hw_param_copy(&par->isp.iso, &cfg->isp.iso);
		break;

	case PARAM_ISP_ADJUST:
		__hw_param_copy(&par->isp.adjust, &cfg->isp.adjust);
		break;

	case PARAM_ISP_METERING:
		__hw_param_copy(&par->isp.metering, &cfg->isp.metering);
		break;

	case PARAM_ISP_AFC:
		__hw_param_copy(&par->isp.afc, &cfg->isp.afc);
		break;

	case PARAM_ISP_OTF_OUTPUT:
		__hw_param_copy(&par->isp.otf_output, &cfg->isp.otf_output);
		break;

	case PARAM_ISP_DMA1_OUTPUT:
		__hw_param_copy(&par->isp.dma1_output, &cfg->isp.dma1_output);
		break;

	case PARAM_ISP_DMA2_OUTPUT:
		__hw_param_copy(&par->isp.dma2_output, &cfg->isp.dma2_output);
		break;

	case PARAM_DRC_CONTROL:
		__hw_param_copy(&par->drc.control, &cfg->drc.control);
		break;

	case PARAM_DRC_OTF_INPUT:
		__hw_param_copy(&par->drc.otf_input, &cfg->drc.otf_input);
		break;

	case PARAM_DRC_DMA_INPUT:
		__hw_param_copy(&par->drc.dma_input, &cfg->drc.dma_input);
		break;

	case PARAM_DRC_OTF_OUTPUT:
		__hw_param_copy(&par->drc.otf_output, &cfg->drc.otf_output);
		break;

	case PARAM_FD_CONTROL:
		__hw_param_copy(&par->fd.control, &cfg->fd.control);
		break;

	case PARAM_FD_OTF_INPUT:
		__hw_param_copy(&par->fd.otf_input, &cfg->fd.otf_input);
		break;

	case PARAM_FD_DMA_INPUT:
		__hw_param_copy(&par->fd.dma_input, &cfg->fd.dma_input);
		break;

	case PARAM_FD_CONFIG:
		__hw_param_copy(&par->fd.config, &cfg->fd.config);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}