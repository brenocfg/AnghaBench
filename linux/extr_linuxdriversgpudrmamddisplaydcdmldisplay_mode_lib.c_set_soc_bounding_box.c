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
struct _vcs_dpi_soc_bounding_box_st {int dummy; } ;
typedef  enum dml_project { ____Placeholder_dml_project } dml_project ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  DML_PROJECT_RAVEN1 128 
 struct _vcs_dpi_soc_bounding_box_st dcn1_0_soc ; 

__attribute__((used)) static void set_soc_bounding_box(struct _vcs_dpi_soc_bounding_box_st *soc, enum dml_project project)
{
	switch (project) {
	case DML_PROJECT_RAVEN1:
		*soc = dcn1_0_soc;
		break;
	default:
		ASSERT(0);
		break;
	}
}