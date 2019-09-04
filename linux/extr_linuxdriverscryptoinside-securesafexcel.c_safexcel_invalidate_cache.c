#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  control0; scalar_t__ refresh; scalar_t__ options; int /*<<< orphan*/  type; } ;
struct safexcel_result_desc {TYPE_1__ control_data; } ;
struct safexcel_crypto_priv {TYPE_2__* ring; } ;
struct safexcel_command_desc {TYPE_1__ control_data; } ;
struct crypto_async_request {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  cdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_INV_TR ; 
 int /*<<< orphan*/  EIP197_TYPE_EXTENDED ; 
 scalar_t__ IS_ERR (struct safexcel_result_desc*) ; 
 int PTR_ERR (struct safexcel_result_desc*) ; 
 struct safexcel_result_desc* safexcel_add_cdesc (struct safexcel_crypto_priv*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct safexcel_result_desc* safexcel_add_rdesc (struct safexcel_crypto_priv*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safexcel_rdr_req_set (struct safexcel_crypto_priv*,int,struct safexcel_result_desc*,struct crypto_async_request*) ; 
 int /*<<< orphan*/  safexcel_ring_rollback_wptr (struct safexcel_crypto_priv*,int /*<<< orphan*/ *) ; 

int safexcel_invalidate_cache(struct crypto_async_request *async,
			      struct safexcel_crypto_priv *priv,
			      dma_addr_t ctxr_dma, int ring)
{
	struct safexcel_command_desc *cdesc;
	struct safexcel_result_desc *rdesc;
	int ret = 0;

	/* Prepare command descriptor */
	cdesc = safexcel_add_cdesc(priv, ring, true, true, 0, 0, 0, ctxr_dma);
	if (IS_ERR(cdesc))
		return PTR_ERR(cdesc);

	cdesc->control_data.type = EIP197_TYPE_EXTENDED;
	cdesc->control_data.options = 0;
	cdesc->control_data.refresh = 0;
	cdesc->control_data.control0 = CONTEXT_CONTROL_INV_TR;

	/* Prepare result descriptor */
	rdesc = safexcel_add_rdesc(priv, ring, true, true, 0, 0);

	if (IS_ERR(rdesc)) {
		ret = PTR_ERR(rdesc);
		goto cdesc_rollback;
	}

	safexcel_rdr_req_set(priv, ring, rdesc, async);

	return ret;

cdesc_rollback:
	safexcel_ring_rollback_wptr(priv, &priv->ring[ring].cdr);

	return ret;
}