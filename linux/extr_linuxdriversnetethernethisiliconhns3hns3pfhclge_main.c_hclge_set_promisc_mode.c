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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_promisc_param {int dummy; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_cmd_set_promisc_mode (struct hclge_dev*,struct hclge_promisc_param*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_promisc_param_init (struct hclge_promisc_param*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_set_promisc_mode(struct hnae3_handle *handle, bool en_uc_pmc,
				   bool en_mc_pmc)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	struct hclge_promisc_param param;

	hclge_promisc_param_init(&param, en_uc_pmc, en_mc_pmc, true,
				 vport->vport_id);
	hclge_cmd_set_promisc_mode(hdev, &param);
}