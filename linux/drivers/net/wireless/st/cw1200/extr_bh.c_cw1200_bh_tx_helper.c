#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wsm_hdr {int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct cw1200_common {int device_can_sleep; int wsm_tx_seq; scalar_t__ wsm_enable_wsm_dumps; int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; int /*<<< orphan*/  bh_tx; } ;
struct TYPE_2__ {size_t (* align_size ) (int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 size_t EFFECTIVE_BUF_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WSM_TX_SEQ (int) ; 
 int WSM_TX_SEQ_MAX ; 
 int /*<<< orphan*/  __cpu_to_le16 (int) ; 
 size_t __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int cw1200_data_write (struct cw1200_common*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  cw1200_debug_tx_burst (struct cw1200_common*) ; 
 int cw1200_device_wakeup (struct cw1200_common*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t stub1 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wsm_alloc_tx_buffer (struct cw1200_common*) ; 
 int wsm_get_tx (struct cw1200_common*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  wsm_release_tx_buffer (struct cw1200_common*,int) ; 
 int /*<<< orphan*/  wsm_txed (struct cw1200_common*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cw1200_bh_tx_helper(struct cw1200_common *priv,
			       int *pending_tx,
			       int *tx_burst)
{
	size_t tx_len;
	u8 *data;
	int ret;
	struct wsm_hdr *wsm;

	if (priv->device_can_sleep) {
		ret = cw1200_device_wakeup(priv);
		if (WARN_ON(ret < 0)) { /* Error in wakeup */
			*pending_tx = 1;
			return 0;
		} else if (ret) { /* Woke up */
			priv->device_can_sleep = false;
		} else { /* Did not awake */
			*pending_tx = 1;
			return 0;
		}
	}

	wsm_alloc_tx_buffer(priv);
	ret = wsm_get_tx(priv, &data, &tx_len, tx_burst);
	if (ret <= 0) {
		wsm_release_tx_buffer(priv, 1);
		if (WARN_ON(ret < 0))
			return ret; /* Error */
		return 0; /* No work */
	}

	wsm = (struct wsm_hdr *)data;
	BUG_ON(tx_len < sizeof(*wsm));
	BUG_ON(__le16_to_cpu(wsm->len) != tx_len);

	atomic_add(1, &priv->bh_tx);

	tx_len = priv->hwbus_ops->align_size(
		priv->hwbus_priv, tx_len);

	/* Check if not exceeding CW1200 capabilities */
	if (WARN_ON_ONCE(tx_len > EFFECTIVE_BUF_SIZE))
		pr_debug("Write aligned len: %zu\n", tx_len);

	wsm->id &= __cpu_to_le16(0xffff ^ WSM_TX_SEQ(WSM_TX_SEQ_MAX));
	wsm->id |= __cpu_to_le16(WSM_TX_SEQ(priv->wsm_tx_seq));

	if (WARN_ON(cw1200_data_write(priv, data, tx_len))) {
		pr_err("tx blew up, len %zu\n", tx_len);
		wsm_release_tx_buffer(priv, 1);
		return -1; /* Error */
	}

	if (priv->wsm_enable_wsm_dumps)
		print_hex_dump_bytes("--> ",
				     DUMP_PREFIX_NONE,
				     data,
				     __le16_to_cpu(wsm->len));

	wsm_txed(priv, data);
	priv->wsm_tx_seq = (priv->wsm_tx_seq + 1) & WSM_TX_SEQ_MAX;

	if (*tx_burst > 1) {
		cw1200_debug_tx_burst(priv);
		return 1; /* Work remains */
	}

	return 0;
}