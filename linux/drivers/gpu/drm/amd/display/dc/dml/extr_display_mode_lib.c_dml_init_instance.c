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
struct _vcs_dpi_ip_params_st {int dummy; } ;
struct _vcs_dpi_soc_bounding_box_st {int dummy; } ;
struct display_mode_lib {int project; int /*<<< orphan*/  funcs; struct _vcs_dpi_ip_params_st ip; struct _vcs_dpi_soc_bounding_box_st soc; } ;
typedef  enum dml_project { ____Placeholder_dml_project } dml_project ;

/* Variables and functions */
#define  DML_PROJECT_DCN21 130 
#define  DML_PROJECT_NAVI10 129 
#define  DML_PROJECT_NAVI10v2 128 
 int /*<<< orphan*/  dml20_funcs ; 
 int /*<<< orphan*/  dml20v2_funcs ; 
 int /*<<< orphan*/  dml21_funcs ; 

void dml_init_instance(struct display_mode_lib *lib,
		const struct _vcs_dpi_soc_bounding_box_st *soc_bb,
		const struct _vcs_dpi_ip_params_st *ip_params,
		enum dml_project project)
{
	lib->soc = *soc_bb;
	lib->ip = *ip_params;
	lib->project = project;
	switch (project) {
#ifdef CONFIG_DRM_AMD_DC_DCN2_0
	case DML_PROJECT_NAVI10:
		lib->funcs = dml20_funcs;
		break;
	case DML_PROJECT_NAVI10v2:
		lib->funcs = dml20v2_funcs;
		break;
#endif
#ifdef CONFIG_DRM_AMD_DC_DCN2_1
        case DML_PROJECT_DCN21:
                lib->funcs = dml21_funcs;
                break;
#endif

	default:
		break;
	}
}