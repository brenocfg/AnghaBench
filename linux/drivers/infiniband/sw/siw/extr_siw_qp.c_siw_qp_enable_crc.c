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
struct siw_rx_stream {TYPE_1__* mpa_crc_hd; } ;
struct siw_iwarp_tx {TYPE_1__* mpa_crc_hd; } ;
struct siw_qp {struct siw_iwarp_tx tx_ctx; struct siw_rx_stream rx_stream; } ;
struct shash_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tfm; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int crypto_shash_descsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * siw_crypto_shash ; 

__attribute__((used)) static int siw_qp_enable_crc(struct siw_qp *qp)
{
	struct siw_rx_stream *c_rx = &qp->rx_stream;
	struct siw_iwarp_tx *c_tx = &qp->tx_ctx;
	int size;

	if (siw_crypto_shash == NULL)
		return -ENOENT;

	size = crypto_shash_descsize(siw_crypto_shash) +
		sizeof(struct shash_desc);

	c_tx->mpa_crc_hd = kzalloc(size, GFP_KERNEL);
	c_rx->mpa_crc_hd = kzalloc(size, GFP_KERNEL);
	if (!c_tx->mpa_crc_hd || !c_rx->mpa_crc_hd) {
		kfree(c_tx->mpa_crc_hd);
		kfree(c_rx->mpa_crc_hd);
		c_tx->mpa_crc_hd = NULL;
		c_rx->mpa_crc_hd = NULL;
		return -ENOMEM;
	}
	c_tx->mpa_crc_hd->tfm = siw_crypto_shash;
	c_rx->mpa_crc_hd->tfm = siw_crypto_shash;

	return 0;
}