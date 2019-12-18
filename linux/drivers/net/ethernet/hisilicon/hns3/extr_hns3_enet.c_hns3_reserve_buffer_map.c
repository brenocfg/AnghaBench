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
struct hns3_enet_ring {int dummy; } ;
struct hns3_desc_cb {int dummy; } ;

/* Variables and functions */
 int hns3_alloc_buffer (struct hns3_enet_ring*,struct hns3_desc_cb*) ; 
 int /*<<< orphan*/  hns3_free_buffer (struct hns3_enet_ring*,struct hns3_desc_cb*) ; 
 int hns3_map_buffer (struct hns3_enet_ring*,struct hns3_desc_cb*) ; 

__attribute__((used)) static int hns3_reserve_buffer_map(struct hns3_enet_ring *ring,
				   struct hns3_desc_cb *cb)
{
	int ret;

	ret = hns3_alloc_buffer(ring, cb);
	if (ret)
		goto out;

	ret = hns3_map_buffer(ring, cb);
	if (ret)
		goto out_with_buf;

	return 0;

out_with_buf:
	hns3_free_buffer(ring, cb);
out:
	return ret;
}