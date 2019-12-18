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
struct hnae3_ring_chain_node {int dummy; } ;
struct hclge_vport {int dummy; } ;
struct hclge_mbx_vf_to_pf_cmd {int* msg; } ;
typedef  int /*<<< orphan*/  ring_chain ;

/* Variables and functions */
 int hclge_bind_ring_with_vector (struct hclge_vport*,int,int,struct hnae3_ring_chain_node*) ; 
 int /*<<< orphan*/  hclge_free_vector_ring_chain (struct hnae3_ring_chain_node*) ; 
 int hclge_get_ring_chain_from_mbx (struct hclge_mbx_vf_to_pf_cmd*,struct hnae3_ring_chain_node*,struct hclge_vport*) ; 
 int /*<<< orphan*/  memset (struct hnae3_ring_chain_node*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_map_unmap_ring_to_vf_vector(struct hclge_vport *vport, bool en,
					     struct hclge_mbx_vf_to_pf_cmd *req)
{
	struct hnae3_ring_chain_node ring_chain;
	int vector_id = req->msg[1];
	int ret;

	memset(&ring_chain, 0, sizeof(ring_chain));
	ret = hclge_get_ring_chain_from_mbx(req, &ring_chain, vport);
	if (ret)
		return ret;

	ret = hclge_bind_ring_with_vector(vport, vector_id, en, &ring_chain);

	hclge_free_vector_ring_chain(&ring_chain);

	return ret;
}