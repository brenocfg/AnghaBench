#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_sdio {int n_rx_pkts; TYPE_1__* rx_pkts; } ;
struct ath10k_htc_hdr {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  eid; } ;
struct ath10k {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  alloc_len; } ;

/* Variables and functions */
 scalar_t__ ATH10K_HIF_MBOX_BLOCK_SIZE ; 
 int ATH10K_HTC_FLAGS_RECV_1MORE_BLOCK ; 
 int ATH10K_HTC_FLAG_BUNDLE_MASK ; 
 int ATH10K_HTC_MBOX_MAX_PAYLOAD_LENGTH ; 
 size_t ATH10K_SDIO_MAX_BUFFER_SIZE ; 
 int ATH10K_SDIO_MAX_RX_MSGS ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t ath10k_sdio_calc_txrx_padded_len (struct ath10k_sdio*,size_t) ; 
 int ath10k_sdio_mbox_alloc_pkt_bundle (struct ath10k*,TYPE_1__*,struct ath10k_htc_hdr*,size_t,size_t,size_t*) ; 
 int ath10k_sdio_mbox_alloc_rx_pkt (TYPE_1__*,size_t,size_t,int,int) ; 
 int /*<<< orphan*/  ath10k_sdio_mbox_free_rx_pkt (TYPE_1__*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_mbox_rx_alloc(struct ath10k *ar,
				     u32 lookaheads[], int n_lookaheads)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct ath10k_htc_hdr *htc_hdr;
	size_t full_len, act_len;
	bool last_in_bundle;
	int ret, i;

	if (n_lookaheads > ATH10K_SDIO_MAX_RX_MSGS) {
		ath10k_warn(ar,
			    "the total number of pkgs to be fetched (%u) exceeds maximum %u\n",
			    n_lookaheads,
			    ATH10K_SDIO_MAX_RX_MSGS);
		ret = -ENOMEM;
		goto err;
	}

	for (i = 0; i < n_lookaheads; i++) {
		htc_hdr = (struct ath10k_htc_hdr *)&lookaheads[i];
		last_in_bundle = false;

		if (le16_to_cpu(htc_hdr->len) >
		    ATH10K_HTC_MBOX_MAX_PAYLOAD_LENGTH) {
			ath10k_warn(ar,
				    "payload length %d exceeds max htc length: %zu\n",
				    le16_to_cpu(htc_hdr->len),
				    ATH10K_HTC_MBOX_MAX_PAYLOAD_LENGTH);
			ret = -ENOMEM;
			goto err;
		}

		act_len = le16_to_cpu(htc_hdr->len) + sizeof(*htc_hdr);
		full_len = ath10k_sdio_calc_txrx_padded_len(ar_sdio, act_len);

		if (full_len > ATH10K_SDIO_MAX_BUFFER_SIZE) {
			ath10k_warn(ar,
				    "rx buffer requested with invalid htc_hdr length (%d, 0x%x): %d\n",
				    htc_hdr->eid, htc_hdr->flags,
				    le16_to_cpu(htc_hdr->len));
			ret = -EINVAL;
			goto err;
		}

		if (htc_hdr->flags & ATH10K_HTC_FLAG_BUNDLE_MASK) {
			/* HTC header indicates that every packet to follow
			 * has the same padded length so that it can be
			 * optimally fetched as a full bundle.
			 */
			size_t bndl_cnt;

			ret = ath10k_sdio_mbox_alloc_pkt_bundle(ar,
								&ar_sdio->rx_pkts[i],
								htc_hdr,
								full_len,
								act_len,
								&bndl_cnt);

			if (ret) {
				ath10k_warn(ar, "alloc_bundle error %d\n", ret);
				goto err;
			}

			n_lookaheads += bndl_cnt;
			i += bndl_cnt;
			/*Next buffer will be the last in the bundle */
			last_in_bundle = true;
		}

		/* Allocate skb for packet. If the packet had the
		 * ATH10K_HTC_FLAG_BUNDLE_MASK flag set, all bundled
		 * packet skb's have been allocated in the previous step.
		 */
		if (htc_hdr->flags & ATH10K_HTC_FLAGS_RECV_1MORE_BLOCK)
			full_len += ATH10K_HIF_MBOX_BLOCK_SIZE;

		ret = ath10k_sdio_mbox_alloc_rx_pkt(&ar_sdio->rx_pkts[i],
						    act_len,
						    full_len,
						    last_in_bundle,
						    last_in_bundle);
		if (ret) {
			ath10k_warn(ar, "alloc_rx_pkt error %d\n", ret);
			goto err;
		}
	}

	ar_sdio->n_rx_pkts = i;

	return 0;

err:
	for (i = 0; i < ATH10K_SDIO_MAX_RX_MSGS; i++) {
		if (!ar_sdio->rx_pkts[i].alloc_len)
			break;
		ath10k_sdio_mbox_free_rx_pkt(&ar_sdio->rx_pkts[i]);
	}

	return ret;
}