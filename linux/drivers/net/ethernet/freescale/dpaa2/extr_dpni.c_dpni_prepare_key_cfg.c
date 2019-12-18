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
typedef  int /*<<< orphan*/  u8 ;
struct dpni_ext_set_rx_tc_dist {int num_extracts; struct dpni_dist_extract* extracts; } ;
struct dpni_dist_extract {TYPE_5__* masks; int /*<<< orphan*/  extract_type; int /*<<< orphan*/  num_of_byte_masks; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  hdr_index; int /*<<< orphan*/  field; int /*<<< orphan*/  efh_type; int /*<<< orphan*/  prot; } ;
struct dpkg_profile_cfg {int num_extracts; TYPE_7__* extracts; } ;
struct TYPE_10__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct TYPE_9__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  hdr_index; int /*<<< orphan*/  field; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  prot; } ;
struct TYPE_11__ {TYPE_3__ from_parse; TYPE_2__ from_data; TYPE_1__ from_hdr; } ;
struct TYPE_14__ {int type; TYPE_6__* masks; int /*<<< orphan*/  num_of_byte_masks; TYPE_4__ extract; } ;
struct TYPE_13__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  mask; } ;
struct TYPE_12__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
#define  DPKG_EXTRACT_FROM_DATA 130 
#define  DPKG_EXTRACT_FROM_HDR 129 
#define  DPKG_EXTRACT_FROM_PARSE 128 
 int DPKG_MAX_NUM_OF_EXTRACTS ; 
 int DPKG_NUM_OF_MASKS ; 
 int /*<<< orphan*/  EFH_TYPE ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXTRACT_TYPE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpni_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int dpni_prepare_key_cfg(const struct dpkg_profile_cfg *cfg, u8 *key_cfg_buf)
{
	int i, j;
	struct dpni_ext_set_rx_tc_dist *dpni_ext;
	struct dpni_dist_extract *extr;

	if (cfg->num_extracts > DPKG_MAX_NUM_OF_EXTRACTS)
		return -EINVAL;

	dpni_ext = (struct dpni_ext_set_rx_tc_dist *)key_cfg_buf;
	dpni_ext->num_extracts = cfg->num_extracts;

	for (i = 0; i < cfg->num_extracts; i++) {
		extr = &dpni_ext->extracts[i];

		switch (cfg->extracts[i].type) {
		case DPKG_EXTRACT_FROM_HDR:
			extr->prot = cfg->extracts[i].extract.from_hdr.prot;
			dpni_set_field(extr->efh_type, EFH_TYPE,
				       cfg->extracts[i].extract.from_hdr.type);
			extr->size = cfg->extracts[i].extract.from_hdr.size;
			extr->offset = cfg->extracts[i].extract.from_hdr.offset;
			extr->field = cpu_to_le32(
				cfg->extracts[i].extract.from_hdr.field);
			extr->hdr_index =
				cfg->extracts[i].extract.from_hdr.hdr_index;
			break;
		case DPKG_EXTRACT_FROM_DATA:
			extr->size = cfg->extracts[i].extract.from_data.size;
			extr->offset =
				cfg->extracts[i].extract.from_data.offset;
			break;
		case DPKG_EXTRACT_FROM_PARSE:
			extr->size = cfg->extracts[i].extract.from_parse.size;
			extr->offset =
				cfg->extracts[i].extract.from_parse.offset;
			break;
		default:
			return -EINVAL;
		}

		extr->num_of_byte_masks = cfg->extracts[i].num_of_byte_masks;
		dpni_set_field(extr->extract_type, EXTRACT_TYPE,
			       cfg->extracts[i].type);

		for (j = 0; j < DPKG_NUM_OF_MASKS; j++) {
			extr->masks[j].mask = cfg->extracts[i].masks[j].mask;
			extr->masks[j].offset =
				cfg->extracts[i].masks[j].offset;
		}
	}

	return 0;
}