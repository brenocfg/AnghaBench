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
struct ipu3_uapi_params {int /*<<< orphan*/  xnr3_dmem_params; int /*<<< orphan*/  tnr3_dmem_params; } ;
struct TYPE_11__ {int y0; int u0; int v0; } ;
struct ipu3_uapi_isp_xnr3_params {int knee_y1; int knee_y2; TYPE_10__ alpha; } ;
struct ipu3_uapi_isp_tnr3_params {int knee_y1; int knee_y2; TYPE_10__ alpha; } ;
struct ipu3_uapi_flags {scalar_t__ xnr3_dmem_params; scalar_t__ tnr3_dmem_params; } ;
struct TYPE_20__ {int /*<<< orphan*/  xnr3; int /*<<< orphan*/  tnr3; } ;
struct imgu_fw_param_memory_offsets {TYPE_9__ dmem; } ;
struct TYPE_16__ {TYPE_4__** params; } ;
struct TYPE_17__ {TYPE_5__ mem_initializers; } ;
struct TYPE_18__ {TYPE_6__ sp; } ;
struct TYPE_19__ {TYPE_7__ isp; } ;
struct TYPE_13__ {int* offsets; } ;
struct TYPE_14__ {TYPE_2__ memory_offsets; } ;
struct imgu_fw_info {TYPE_8__ info; TYPE_3__ blob; } ;
struct imgu_css_pipe {size_t bindex; scalar_t__ pipe_id; } ;
struct imgu_css {TYPE_1__* fwp; struct imgu_css_pipe* pipes; } ;
typedef  enum imgu_abi_param_class { ____Placeholder_imgu_abi_param_class } imgu_abi_param_class ;
typedef  enum imgu_abi_memories { ____Placeholder_imgu_abi_memories } imgu_abi_memories ;
struct TYPE_15__ {int /*<<< orphan*/  size; } ;
struct TYPE_12__ {struct imgu_fw_info* binary_header; } ;

/* Variables and functions */
 int EPROTO ; 
 int IMGU_ABI_MEM_ISP_DMEM0 ; 
 size_t IMGU_ABI_PARAM_CLASS_PARAM ; 
 scalar_t__ IPU3_CSS_PIPE_ID_VIDEO ; 
 scalar_t__ IS_ERR (struct ipu3_uapi_isp_xnr3_params*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct ipu3_uapi_isp_xnr3_params*) ; 
 struct ipu3_uapi_isp_xnr3_params* imgu_css_cfg_copy (struct imgu_css*,unsigned int,int,int /*<<< orphan*/ *,void*,void*,int const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int imgu_css_cfg_dmem0(struct imgu_css *css, unsigned int pipe,
		       struct ipu3_uapi_flags *use,
		       void *dmem0, void *dmem0_old,
		       struct ipu3_uapi_params *user)
{
	struct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	const struct imgu_fw_info *bi =
		&css->fwp->binary_header[css_pipe->bindex];
	struct imgu_fw_param_memory_offsets *pofs = (void *)css->fwp +
		bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_PARAM];

	struct ipu3_uapi_isp_tnr3_params *tnr_dmem = NULL;
	struct ipu3_uapi_isp_xnr3_params *xnr_dmem;

	const enum imgu_abi_param_class c = IMGU_ABI_PARAM_CLASS_PARAM;
	const enum imgu_abi_memories m = IMGU_ABI_MEM_ISP_DMEM0;

	/* Configure DMEM0 */

	memset(dmem0, 0, bi->info.isp.sp.mem_initializers.params[c][m].size);

	/* Configure TNR3 DMEM0 parameters */
	if (css_pipe->pipe_id == IPU3_CSS_PIPE_ID_VIDEO) {
		tnr_dmem = imgu_css_cfg_copy(css, pipe,
					     use && use->tnr3_dmem_params,
					     &user->tnr3_dmem_params,
					     dmem0_old, dmem0, m,
					     &pofs->dmem.tnr3,
					     sizeof(*tnr_dmem));
		if (!IS_ERR_OR_NULL(tnr_dmem)) {
			/* Generate parameter from scratch */
			tnr_dmem->knee_y1 = 768;
			tnr_dmem->knee_y2 = 1280;
		}
	}

	/* Configure XNR3 DMEM0 parameters */

	xnr_dmem = imgu_css_cfg_copy(css, pipe, use && use->xnr3_dmem_params,
				     &user->xnr3_dmem_params, dmem0_old, dmem0,
				     m, &pofs->dmem.xnr3, sizeof(*xnr_dmem));
	if (!IS_ERR_OR_NULL(xnr_dmem)) {
		/* Generate parameter from scratch */
		xnr_dmem->alpha.y0 = 2047;
		xnr_dmem->alpha.u0 = 2047;
		xnr_dmem->alpha.v0 = 2047;
	}

	return IS_ERR(tnr_dmem) || IS_ERR(xnr_dmem) ? -EPROTO : 0;
}