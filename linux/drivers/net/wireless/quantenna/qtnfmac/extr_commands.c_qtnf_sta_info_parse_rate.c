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
struct rate_info {int legacy; int /*<<< orphan*/  flags; int /*<<< orphan*/  bw; int /*<<< orphan*/  nss; int /*<<< orphan*/  mcs; } ;
struct qlink_sta_info_rate {int bw; int flags; int /*<<< orphan*/  nss; int /*<<< orphan*/  mcs; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
#define  QLINK_CHAN_WIDTH_10 134 
#define  QLINK_CHAN_WIDTH_160 133 
#define  QLINK_CHAN_WIDTH_20 132 
#define  QLINK_CHAN_WIDTH_20_NOHT 131 
#define  QLINK_CHAN_WIDTH_40 130 
#define  QLINK_CHAN_WIDTH_5 129 
#define  QLINK_CHAN_WIDTH_80 128 
 int QLINK_STA_INFO_RATE_FLAG_HT_MCS ; 
 int QLINK_STA_INFO_RATE_FLAG_SHORT_GI ; 
 int QLINK_STA_INFO_RATE_FLAG_VHT_MCS ; 
 int /*<<< orphan*/  RATE_INFO_BW_10 ; 
 int /*<<< orphan*/  RATE_INFO_BW_160 ; 
 int /*<<< orphan*/  RATE_INFO_BW_20 ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RATE_INFO_BW_5 ; 
 int /*<<< orphan*/  RATE_INFO_BW_80 ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_VHT_MCS ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qtnf_sta_info_parse_rate(struct rate_info *rate_dst,
			 const struct qlink_sta_info_rate *rate_src)
{
	rate_dst->legacy = get_unaligned_le16(&rate_src->rate) * 10;

	rate_dst->mcs = rate_src->mcs;
	rate_dst->nss = rate_src->nss;
	rate_dst->flags = 0;

	switch (rate_src->bw) {
	case QLINK_CHAN_WIDTH_5:
		rate_dst->bw = RATE_INFO_BW_5;
		break;
	case QLINK_CHAN_WIDTH_10:
		rate_dst->bw = RATE_INFO_BW_10;
		break;
	case QLINK_CHAN_WIDTH_20:
	case QLINK_CHAN_WIDTH_20_NOHT:
		rate_dst->bw = RATE_INFO_BW_20;
		break;
	case QLINK_CHAN_WIDTH_40:
		rate_dst->bw = RATE_INFO_BW_40;
		break;
	case QLINK_CHAN_WIDTH_80:
		rate_dst->bw = RATE_INFO_BW_80;
		break;
	case QLINK_CHAN_WIDTH_160:
		rate_dst->bw = RATE_INFO_BW_160;
		break;
	default:
		rate_dst->bw = 0;
		break;
	}

	if (rate_src->flags & QLINK_STA_INFO_RATE_FLAG_HT_MCS)
		rate_dst->flags |= RATE_INFO_FLAGS_MCS;
	else if (rate_src->flags & QLINK_STA_INFO_RATE_FLAG_VHT_MCS)
		rate_dst->flags |= RATE_INFO_FLAGS_VHT_MCS;

	if (rate_src->flags & QLINK_STA_INFO_RATE_FLAG_SHORT_GI)
		rate_dst->flags |= RATE_INFO_FLAGS_SHORT_GI;
}