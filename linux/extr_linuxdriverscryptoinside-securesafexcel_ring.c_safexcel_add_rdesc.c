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
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_result_desc {int first_seg; int last_seg; int /*<<< orphan*/  data_hi; int /*<<< orphan*/  data_lo; int /*<<< orphan*/  particle_size; } ;
struct safexcel_crypto_priv {TYPE_1__* ring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  rdr; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct safexcel_result_desc*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct safexcel_result_desc*,int /*<<< orphan*/ ,int) ; 
 struct safexcel_result_desc* safexcel_ring_next_wptr (struct safexcel_crypto_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

struct safexcel_result_desc *safexcel_add_rdesc(struct safexcel_crypto_priv *priv,
						int ring_id,
						bool first, bool last,
						dma_addr_t data, u32 len)
{
	struct safexcel_result_desc *rdesc;

	rdesc = safexcel_ring_next_wptr(priv, &priv->ring[ring_id].rdr);
	if (IS_ERR(rdesc))
		return rdesc;

	memset(rdesc, 0, sizeof(struct safexcel_result_desc));

	rdesc->first_seg = first;
	rdesc->last_seg = last;
	rdesc->particle_size = len;
	rdesc->data_lo = lower_32_bits(data);
	rdesc->data_hi = upper_32_bits(data);

	return rdesc;
}