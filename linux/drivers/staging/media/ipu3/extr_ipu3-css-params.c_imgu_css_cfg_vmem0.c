#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct ipu3_uapi_params {int /*<<< orphan*/  xnr3_vmem_params; int /*<<< orphan*/  tnr3_vmem_params; int /*<<< orphan*/  lin_vmem_params; } ;
struct ipu3_uapi_isp_xnr3_vmem_params {int* lin_lutlow_gr; int* lin_lutlow_r; int* lin_lutlow_b; int* lin_lutlow_gb; int* lin_lutdif_gr; int* lin_lutdif_r; int* lin_lutdif_b; int* lin_lutdif_gb; int* sigma; int /*<<< orphan*/ * c; int /*<<< orphan*/ * b; int /*<<< orphan*/ * a; int /*<<< orphan*/ * x; } ;
struct ipu3_uapi_isp_tnr3_vmem_params {int* lin_lutlow_gr; int* lin_lutlow_r; int* lin_lutlow_b; int* lin_lutlow_gb; int* lin_lutdif_gr; int* lin_lutdif_r; int* lin_lutdif_b; int* lin_lutdif_gb; int* sigma; int /*<<< orphan*/ * c; int /*<<< orphan*/ * b; int /*<<< orphan*/ * a; int /*<<< orphan*/ * x; } ;
struct ipu3_uapi_isp_lin_vmem_params {int* lin_lutlow_gr; int* lin_lutlow_r; int* lin_lutlow_b; int* lin_lutlow_gb; int* lin_lutdif_gr; int* lin_lutdif_r; int* lin_lutdif_b; int* lin_lutdif_gb; int* sigma; int /*<<< orphan*/ * c; int /*<<< orphan*/ * b; int /*<<< orphan*/ * a; int /*<<< orphan*/ * x; } ;
struct ipu3_uapi_flags {scalar_t__ xnr3_vmem_params; scalar_t__ tnr3_vmem_params; scalar_t__ lin_vmem_params; } ;
struct TYPE_12__ {int /*<<< orphan*/  xnr3; int /*<<< orphan*/  tnr3; int /*<<< orphan*/  lin; } ;
struct imgu_fw_param_memory_offsets {TYPE_10__ vmem; } ;
struct TYPE_18__ {TYPE_4__** params; } ;
struct TYPE_19__ {TYPE_5__ mem_initializers; } ;
struct TYPE_20__ {TYPE_6__ sp; } ;
struct TYPE_21__ {TYPE_7__ isp; } ;
struct TYPE_15__ {int* offsets; } ;
struct TYPE_16__ {TYPE_2__ memory_offsets; } ;
struct imgu_fw_info {TYPE_8__ info; TYPE_3__ blob; } ;
struct imgu_css {TYPE_9__* pipes; TYPE_1__* fwp; } ;
typedef  enum imgu_abi_param_class { ____Placeholder_imgu_abi_param_class } imgu_abi_param_class ;
typedef  enum imgu_abi_memories { ____Placeholder_imgu_abi_memories } imgu_abi_memories ;
struct TYPE_22__ {size_t bindex; scalar_t__ pipe_id; } ;
struct TYPE_17__ {int /*<<< orphan*/  size; } ;
struct TYPE_14__ {struct imgu_fw_info* binary_header; } ;
struct TYPE_13__ {int /*<<< orphan*/ * c; int /*<<< orphan*/ * b; int /*<<< orphan*/ * a; int /*<<< orphan*/ * x; } ;

/* Variables and functions */
 int EPROTO ; 
 int IMGU_ABI_MEM_ISP_VMEM0 ; 
 size_t IMGU_ABI_PARAM_CLASS_PARAM ; 
 unsigned int IMGU_XNR3_VMEM_LUT_LEN ; 
 scalar_t__ IPU3_CSS_PIPE_ID_VIDEO ; 
 unsigned int IPU3_UAPI_ISP_TNR3_VMEM_LEN ; 
 unsigned int IPU3_UAPI_LIN_LUT_SIZE ; 
 scalar_t__ IS_ERR (struct ipu3_uapi_isp_xnr3_vmem_params*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct ipu3_uapi_isp_xnr3_vmem_params*) ; 
 struct ipu3_uapi_isp_xnr3_vmem_params* imgu_css_cfg_copy (struct imgu_css*,unsigned int,int,int /*<<< orphan*/ *,void*,void*,int const,int /*<<< orphan*/ *,int) ; 
 TYPE_11__ imgu_css_xnr3_vmem_defaults ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int imgu_css_cfg_vmem0(struct imgu_css *css, unsigned int pipe,
		       struct ipu3_uapi_flags *use,
		       void *vmem0, void *vmem0_old,
		       struct ipu3_uapi_params *user)
{
	const struct imgu_fw_info *bi =
		&css->fwp->binary_header[css->pipes[pipe].bindex];
	struct imgu_fw_param_memory_offsets *pofs = (void *)css->fwp +
		bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_PARAM];
	struct ipu3_uapi_isp_lin_vmem_params *lin_vmem = NULL;
	struct ipu3_uapi_isp_tnr3_vmem_params *tnr_vmem = NULL;
	struct ipu3_uapi_isp_xnr3_vmem_params *xnr_vmem = NULL;
	const enum imgu_abi_param_class c = IMGU_ABI_PARAM_CLASS_PARAM;
	const enum imgu_abi_memories m = IMGU_ABI_MEM_ISP_VMEM0;
	unsigned int i;

	/* Configure VMEM0 */

	memset(vmem0, 0, bi->info.isp.sp.mem_initializers.params[c][m].size);

	/* Configure Linearization VMEM0 parameters */

	lin_vmem = imgu_css_cfg_copy(css, pipe, use && use->lin_vmem_params,
				     &user->lin_vmem_params, vmem0_old, vmem0,
				     m, &pofs->vmem.lin, sizeof(*lin_vmem));
	if (!IS_ERR_OR_NULL(lin_vmem)) {
		/* Generate parameter from scratch */
		for (i = 0; i < IPU3_UAPI_LIN_LUT_SIZE; i++) {
			lin_vmem->lin_lutlow_gr[i] = 32 * i;
			lin_vmem->lin_lutlow_r[i] = 32 * i;
			lin_vmem->lin_lutlow_b[i] = 32 * i;
			lin_vmem->lin_lutlow_gb[i] = 32 * i;

			lin_vmem->lin_lutdif_gr[i] = 32;
			lin_vmem->lin_lutdif_r[i] = 32;
			lin_vmem->lin_lutdif_b[i] = 32;
			lin_vmem->lin_lutdif_gb[i] = 32;
		}
	}

	/* Configure TNR3 VMEM parameters */
	if (css->pipes[pipe].pipe_id == IPU3_CSS_PIPE_ID_VIDEO) {
		tnr_vmem = imgu_css_cfg_copy(css, pipe,
					     use && use->tnr3_vmem_params,
					     &user->tnr3_vmem_params,
					     vmem0_old, vmem0, m,
					     &pofs->vmem.tnr3,
					     sizeof(*tnr_vmem));
		if (!IS_ERR_OR_NULL(tnr_vmem)) {
			/* Generate parameter from scratch */
			for (i = 0; i < IPU3_UAPI_ISP_TNR3_VMEM_LEN; i++)
				tnr_vmem->sigma[i] = 256;
		}
	}
	i = IPU3_UAPI_ISP_TNR3_VMEM_LEN;

	/* Configure XNR3 VMEM parameters */

	xnr_vmem = imgu_css_cfg_copy(css, pipe, use && use->xnr3_vmem_params,
				     &user->xnr3_vmem_params, vmem0_old, vmem0,
				     m, &pofs->vmem.xnr3, sizeof(*xnr_vmem));
	if (!IS_ERR_OR_NULL(xnr_vmem)) {
		xnr_vmem->x[i] = imgu_css_xnr3_vmem_defaults.x
			[i % IMGU_XNR3_VMEM_LUT_LEN];
		xnr_vmem->a[i] = imgu_css_xnr3_vmem_defaults.a
			[i % IMGU_XNR3_VMEM_LUT_LEN];
		xnr_vmem->b[i] = imgu_css_xnr3_vmem_defaults.b
			[i % IMGU_XNR3_VMEM_LUT_LEN];
		xnr_vmem->c[i] = imgu_css_xnr3_vmem_defaults.c
			[i % IMGU_XNR3_VMEM_LUT_LEN];
	}

	return IS_ERR(lin_vmem) || IS_ERR(tnr_vmem) || IS_ERR(xnr_vmem) ?
		-EPROTO : 0;
}