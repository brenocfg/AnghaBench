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
typedef  int /*<<< orphan*/  uint32_t ;
struct _vcs_dpi_soc_bounding_box_st {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASICREV_IS_NAVI12_P (int /*<<< orphan*/ ) ; 
 struct _vcs_dpi_soc_bounding_box_st dcn2_0_nv12_soc ; 
 struct _vcs_dpi_soc_bounding_box_st dcn2_0_soc ; 

__attribute__((used)) static struct _vcs_dpi_soc_bounding_box_st *get_asic_rev_soc_bb(
	uint32_t hw_internal_rev)
{
	if (ASICREV_IS_NAVI12_P(hw_internal_rev))
		return &dcn2_0_nv12_soc;

	return &dcn2_0_soc;
}