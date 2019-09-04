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
struct icp_qat_uof_uword_block {scalar_t__ uword_offset; } ;
struct icp_qat_uof_objtable {int entry_num; } ;
struct icp_qat_uof_image {int dummy; } ;
struct icp_qat_uof_encap_obj {int beg_uof; } ;
struct icp_qat_uof_code_page {int code_area_offset; int /*<<< orphan*/  beg_addr_p; int /*<<< orphan*/  beg_addr_v; int /*<<< orphan*/  page_region; int /*<<< orphan*/  def_page; } ;
struct icp_qat_uof_code_area {scalar_t__ uword_block_tab; int /*<<< orphan*/  micro_words_num; } ;
struct icp_qat_uclo_encap_uwblock {scalar_t__ micro_words; } ;
struct icp_qat_uclo_encap_page {int uwblock_num; struct icp_qat_uclo_encap_uwblock* uwblock; int /*<<< orphan*/  micro_words_num; int /*<<< orphan*/  beg_addr_p; int /*<<< orphan*/  beg_addr_v; int /*<<< orphan*/  page_region; int /*<<< orphan*/  def_page; } ;

/* Variables and functions */

__attribute__((used)) static void qat_uclo_map_image_page(struct icp_qat_uof_encap_obj
				     *encap_uof_obj,
				     struct icp_qat_uof_image *img,
				     struct icp_qat_uclo_encap_page *page)
{
	struct icp_qat_uof_code_page *code_page;
	struct icp_qat_uof_code_area *code_area;
	struct icp_qat_uof_objtable *uword_block_tab;
	struct icp_qat_uof_uword_block *uwblock;
	int i;

	code_page = (struct icp_qat_uof_code_page *)
			((char *)img + sizeof(struct icp_qat_uof_image));
	page->def_page = code_page->def_page;
	page->page_region = code_page->page_region;
	page->beg_addr_v = code_page->beg_addr_v;
	page->beg_addr_p = code_page->beg_addr_p;
	code_area = (struct icp_qat_uof_code_area *)(encap_uof_obj->beg_uof +
						code_page->code_area_offset);
	page->micro_words_num = code_area->micro_words_num;
	uword_block_tab = (struct icp_qat_uof_objtable *)
			  (encap_uof_obj->beg_uof +
			  code_area->uword_block_tab);
	page->uwblock_num = uword_block_tab->entry_num;
	uwblock = (struct icp_qat_uof_uword_block *)((char *)uword_block_tab +
			sizeof(struct icp_qat_uof_objtable));
	page->uwblock = (struct icp_qat_uclo_encap_uwblock *)uwblock;
	for (i = 0; i < uword_block_tab->entry_num; i++)
		page->uwblock[i].micro_words =
		(uintptr_t)encap_uof_obj->beg_uof + uwblock[i].uword_offset;
}