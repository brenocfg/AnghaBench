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
struct hclge_vport {int /*<<< orphan*/  back; int /*<<< orphan*/  vport_id; } ;
struct hclge_promisc_param {int dummy; } ;
struct hclge_mbx_vf_to_pf_cmd {scalar_t__* msg; } ;

/* Variables and functions */
 int hclge_cmd_set_promisc_mode (int /*<<< orphan*/ ,struct hclge_promisc_param*) ; 
 int /*<<< orphan*/  hclge_promisc_param_init (struct hclge_promisc_param*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_vf_promisc_mode(struct hclge_vport *vport,
				     struct hclge_mbx_vf_to_pf_cmd *req)
{
	bool en_bc = req->msg[1] ? true : false;
	struct hclge_promisc_param param;

	/* vf is not allowed to enable unicast/multicast broadcast */
	hclge_promisc_param_init(&param, false, false, en_bc, vport->vport_id);
	return hclge_cmd_set_promisc_mode(vport->back, &param);
}