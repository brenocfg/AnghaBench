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
typedef  int /*<<< orphan*/  u32 ;
struct skb_checksum_ops {int /*<<< orphan*/  combine; int /*<<< orphan*/  update; } ;
struct siw_rx_stream {int /*<<< orphan*/  mpa_crc_hd; int /*<<< orphan*/  skb_offset; int /*<<< orphan*/  skb; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct skb_checksum_ops const*) ; 
 scalar_t__ shash_desc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_csum_combine ; 
 int /*<<< orphan*/  siw_csum_update ; 

__attribute__((used)) static inline void siw_crc_skb(struct siw_rx_stream *srx, unsigned int len)
{
	const struct skb_checksum_ops siw_cs_ops = {
		.update = siw_csum_update,
		.combine = siw_csum_combine,
	};
	__wsum crc = *(u32 *)shash_desc_ctx(srx->mpa_crc_hd);

	crc = __skb_checksum(srx->skb, srx->skb_offset, len, crc,
			     &siw_cs_ops);
	*(u32 *)shash_desc_ctx(srx->mpa_crc_hd) = crc;
}