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
struct ulp_cid_info {struct ulp_cid_info* cid_array; } ;
struct TYPE_2__ {int /*<<< orphan*/  ulp_supported; } ;
struct beiscsi_hba {struct ulp_cid_info** cid_array_info; TYPE_1__ fw_config; struct ulp_cid_info* conn_table; struct ulp_cid_info* ep_array; struct ulp_cid_info* eh_sgl_hndl_base; struct ulp_cid_info* io_sgl_hndl_base; } ;

/* Variables and functions */
 int BEISCSI_ULP_COUNT ; 
 int /*<<< orphan*/  kfree (struct ulp_cid_info*) ; 
 scalar_t__ test_bit (int,void*) ; 

__attribute__((used)) static void beiscsi_cleanup_port(struct beiscsi_hba *phba)
{
	struct ulp_cid_info *ptr_cid_info = NULL;
	int ulp_num;

	kfree(phba->io_sgl_hndl_base);
	kfree(phba->eh_sgl_hndl_base);
	kfree(phba->ep_array);
	kfree(phba->conn_table);

	for (ulp_num = 0; ulp_num < BEISCSI_ULP_COUNT; ulp_num++) {
		if (test_bit(ulp_num, (void *)&phba->fw_config.ulp_supported)) {
			ptr_cid_info = phba->cid_array_info[ulp_num];

			if (ptr_cid_info) {
				kfree(ptr_cid_info->cid_array);
				kfree(ptr_cid_info);
				phba->cid_array_info[ulp_num] = NULL;
			}
		}
	}
}