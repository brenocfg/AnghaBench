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
struct hns3_enet_ring {scalar_t__ desc_num; scalar_t__ buf_size; int /*<<< orphan*/ * desc_cb; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNAE3_IS_TX_RING (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hns3_alloc_desc (struct hns3_enet_ring*) ; 
 int hns3_alloc_ring_buffers (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  hns3_free_desc (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  ring_to_dev (struct hns3_enet_ring*) ; 

__attribute__((used)) static int hns3_alloc_ring_memory(struct hns3_enet_ring *ring)
{
	int ret;

	if (ring->desc_num <= 0 || ring->buf_size <= 0)
		return -EINVAL;

	ring->desc_cb = devm_kcalloc(ring_to_dev(ring), ring->desc_num,
				     sizeof(ring->desc_cb[0]), GFP_KERNEL);
	if (!ring->desc_cb) {
		ret = -ENOMEM;
		goto out;
	}

	ret = hns3_alloc_desc(ring);
	if (ret)
		goto out_with_desc_cb;

	if (!HNAE3_IS_TX_RING(ring)) {
		ret = hns3_alloc_ring_buffers(ring);
		if (ret)
			goto out_with_desc;
	}

	return 0;

out_with_desc:
	hns3_free_desc(ring);
out_with_desc_cb:
	devm_kfree(ring_to_dev(ring), ring->desc_cb);
	ring->desc_cb = NULL;
out:
	return ret;
}