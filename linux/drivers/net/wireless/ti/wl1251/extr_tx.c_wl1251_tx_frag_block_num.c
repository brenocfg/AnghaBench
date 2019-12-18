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
typedef  int u16 ;
struct tx_double_buffer_desc {int num_mem_blocks; int /*<<< orphan*/  length; int /*<<< orphan*/  frag_threshold; } ;

/* Variables and functions */
 int HW_BLOCK_SIZE ; 
 int IEEE80211_MAX_FRAG_THRESHOLD ; 
 int MAX_MPDU_HEADER_AND_SECURITY ; 
 int MAX_MSDU_SECURITY_LENGTH ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,int) ; 

__attribute__((used)) static void wl1251_tx_frag_block_num(struct tx_double_buffer_desc *tx_hdr)
{
	u16 payload_len, frag_threshold, mem_blocks;
	u16 num_mpdus, mem_blocks_per_frag;

	frag_threshold = IEEE80211_MAX_FRAG_THRESHOLD;
	tx_hdr->frag_threshold = cpu_to_le16(frag_threshold);

	payload_len = le16_to_cpu(tx_hdr->length) + MAX_MSDU_SECURITY_LENGTH;

	if (payload_len > frag_threshold) {
		mem_blocks_per_frag =
			((frag_threshold + MAX_MPDU_HEADER_AND_SECURITY) /
			 HW_BLOCK_SIZE) + 1;
		num_mpdus = payload_len / frag_threshold;
		mem_blocks = num_mpdus * mem_blocks_per_frag;
		payload_len -= num_mpdus * frag_threshold;
		num_mpdus++;

	} else {
		mem_blocks_per_frag = 0;
		mem_blocks = 0;
		num_mpdus = 1;
	}

	mem_blocks += (payload_len / HW_BLOCK_SIZE) + 1;

	if (num_mpdus > 1)
		mem_blocks += min(num_mpdus, mem_blocks_per_frag);

	tx_hdr->num_mem_blocks = mem_blocks;
}