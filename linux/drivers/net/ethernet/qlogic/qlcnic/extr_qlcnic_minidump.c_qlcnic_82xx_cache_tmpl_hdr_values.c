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
struct qlcnic_fw_dump {int use_pex_dma; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  offset; int /*<<< orphan*/  num_entries; int /*<<< orphan*/  version; int /*<<< orphan*/  tmpl_hdr_size; struct qlcnic_82xx_dump_template_hdr* tmpl_hdr; } ;
struct qlcnic_82xx_dump_template_hdr {int capabilities; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  drv_cap_mask; int /*<<< orphan*/  offset; int /*<<< orphan*/  num_entries; int /*<<< orphan*/  version; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int BIT_0 ; 

void qlcnic_82xx_cache_tmpl_hdr_values(struct qlcnic_fw_dump *fw_dump)
{
	struct qlcnic_82xx_dump_template_hdr *hdr;

	hdr = fw_dump->tmpl_hdr;
	fw_dump->tmpl_hdr_size = hdr->size;
	fw_dump->version = hdr->version;
	fw_dump->num_entries = hdr->num_entries;
	fw_dump->offset = hdr->offset;

	hdr->drv_cap_mask = hdr->cap_mask;
	fw_dump->cap_mask = hdr->cap_mask;

	fw_dump->use_pex_dma = (hdr->capabilities & BIT_0) ? true : false;
}