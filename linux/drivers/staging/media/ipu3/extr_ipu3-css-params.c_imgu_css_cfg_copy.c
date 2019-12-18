#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct imgu_fw_isp_parameter {int dummy; } ;
struct imgu_css {int dummy; } ;
typedef  enum imgu_abi_param_class { ____Placeholder_imgu_abi_param_class } imgu_abi_param_class ;
typedef  enum imgu_abi_memories { ____Placeholder_imgu_abi_memories } imgu_abi_memories ;

/* Variables and functions */
 int /*<<< orphan*/  EPROTO ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IMGU_ABI_PARAM_CLASS_PARAM ; 
 void* imgu_css_fw_pipeline_params (struct imgu_css*,unsigned int,int const,int,struct imgu_fw_isp_parameter*,size_t,void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static void *imgu_css_cfg_copy(struct imgu_css *css,
			       unsigned int pipe, bool use_user,
			       void *user_setting, void *old_binary_params,
			       void *new_binary_params,
			       enum imgu_abi_memories m,
			       struct imgu_fw_isp_parameter *par,
			       size_t par_size)
{
	const enum imgu_abi_param_class c = IMGU_ABI_PARAM_CLASS_PARAM;
	void *new_setting, *old_setting;

	new_setting = imgu_css_fw_pipeline_params(css, pipe, c, m, par,
						  par_size, new_binary_params);
	if (!new_setting)
		return ERR_PTR(-EPROTO);	/* Corrupted firmware */

	if (use_user) {
		/* Take new user parameters */
		memcpy(new_setting, user_setting, par_size);
	} else if (old_binary_params) {
		/* Take previous value */
		old_setting = imgu_css_fw_pipeline_params(css, pipe, c, m, par,
							  par_size,
							  old_binary_params);
		if (!old_setting)
			return ERR_PTR(-EPROTO);
		memcpy(new_setting, old_setting, par_size);
	} else {
		return new_setting;	/* Need to calculate */
	}

	return NULL;		/* Copied from other value */
}