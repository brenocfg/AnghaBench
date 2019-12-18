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
typedef  union dc_tiling_info {int dummy; } dc_tiling_info ;
struct pte_setting {unsigned int min_pte_before_flip_vert_scan; unsigned int min_pte_before_flip_horiz_scan; int /*<<< orphan*/  pte_req_per_chunk; int /*<<< orphan*/  page_height; int /*<<< orphan*/  page_width; } ;
struct mem_input {int dummy; } ;
struct dce_mem_input {int dummy; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
typedef  enum mi_tiling_format { ____Placeholder_mi_tiling_format } mi_tiling_format ;
typedef  enum mi_bits_per_pixel { ____Placeholder_mi_bits_per_pixel } mi_bits_per_pixel ;
typedef  enum dc_rotation_angle { ____Placeholder_dc_rotation_angle } dc_rotation_angle ;

/* Variables and functions */
 int /*<<< orphan*/  DVMM_MAX_PTE_REQ_OUTSTANDING ; 
 int /*<<< orphan*/  DVMM_MIN_PTE_BEFORE_FLIP ; 
 int /*<<< orphan*/  DVMM_PAGE_HEIGHT ; 
 int /*<<< orphan*/  DVMM_PAGE_WIDTH ; 
 int /*<<< orphan*/  DVMM_PTE_ARB_CONTROL ; 
 int /*<<< orphan*/  DVMM_PTE_CONTROL ; 
 int /*<<< orphan*/  DVMM_PTE_REQ_PER_CHUNK ; 
 int /*<<< orphan*/  GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 struct dce_mem_input* TO_DCE_MEM_INPUT (struct mem_input*) ; 
 int get_mi_bpp (int) ; 
 int get_mi_tiling (union dc_tiling_info*) ; 
 scalar_t__ is_vert_scan (int) ; 
 unsigned int log_2 (int /*<<< orphan*/ ) ; 
 struct pte_setting** pte_settings ; 

__attribute__((used)) static void dce_mi_program_pte_vm(
		struct mem_input *mi,
		enum surface_pixel_format format,
		union dc_tiling_info *tiling_info,
		enum dc_rotation_angle rotation)
{
	struct dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	enum mi_bits_per_pixel mi_bpp = get_mi_bpp(format);
	enum mi_tiling_format mi_tiling = get_mi_tiling(tiling_info);
	const struct pte_setting *pte = &pte_settings[mi_tiling][mi_bpp];

	unsigned int page_width = log_2(pte->page_width);
	unsigned int page_height = log_2(pte->page_height);
	unsigned int min_pte_before_flip = is_vert_scan(rotation) ?
			pte->min_pte_before_flip_vert_scan :
			pte->min_pte_before_flip_horiz_scan;

	REG_UPDATE(GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT,
			GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT, 0x7f);

	REG_UPDATE_3(DVMM_PTE_CONTROL,
			DVMM_PAGE_WIDTH, page_width,
			DVMM_PAGE_HEIGHT, page_height,
			DVMM_MIN_PTE_BEFORE_FLIP, min_pte_before_flip);

	REG_UPDATE_2(DVMM_PTE_ARB_CONTROL,
			DVMM_PTE_REQ_PER_CHUNK, pte->pte_req_per_chunk,
			DVMM_MAX_PTE_REQ_OUTSTANDING, 0x7f);
}