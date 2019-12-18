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
struct ibmvnic_long_term_buff {int /*<<< orphan*/  size; int /*<<< orphan*/  map_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  buff; } ;
struct ibmvnic_adapter {TYPE_1__* vdev; scalar_t__ fw_done_rc; int /*<<< orphan*/  fw_done; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int alloc_long_term_buff (struct ibmvnic_adapter*,struct ibmvnic_long_term_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_long_term_buff (struct ibmvnic_adapter*,struct ibmvnic_long_term_buff*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send_request_map (struct ibmvnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reset_long_term_buff(struct ibmvnic_adapter *adapter,
				struct ibmvnic_long_term_buff *ltb)
{
	int rc;

	memset(ltb->buff, 0, ltb->size);

	init_completion(&adapter->fw_done);
	rc = send_request_map(adapter, ltb->addr, ltb->size, ltb->map_id);
	if (rc)
		return rc;
	wait_for_completion(&adapter->fw_done);

	if (adapter->fw_done_rc) {
		dev_info(&adapter->vdev->dev,
			 "Reset failed, attempting to free and reallocate buffer\n");
		free_long_term_buff(adapter, ltb);
		return alloc_long_term_buff(adapter, ltb, ltb->size);
	}
	return 0;
}