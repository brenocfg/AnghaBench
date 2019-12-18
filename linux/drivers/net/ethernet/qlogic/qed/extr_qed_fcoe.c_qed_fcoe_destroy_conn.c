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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hash_fcoe_con {struct qed_fcoe_conn* con; } ;
struct qed_fcoe_conn {int /*<<< orphan*/  terminate_params; } ;
struct qed_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_AFFIN_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 struct qed_hash_fcoe_con* qed_fcoe_get_hash (struct qed_dev*,int /*<<< orphan*/ ) ; 
 int qed_sp_fcoe_conn_destroy (int /*<<< orphan*/ ,struct qed_fcoe_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_fcoe_destroy_conn(struct qed_dev *cdev,
				 u32 handle, dma_addr_t terminate_params)
{
	struct qed_hash_fcoe_con *hash_con;
	struct qed_fcoe_conn *con;

	hash_con = qed_fcoe_get_hash(cdev, handle);
	if (!hash_con) {
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		return -EINVAL;
	}

	/* Update the connection with information from the params */
	con = hash_con->con;
	con->terminate_params = terminate_params;

	return qed_sp_fcoe_conn_destroy(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBLOCK, NULL);
}