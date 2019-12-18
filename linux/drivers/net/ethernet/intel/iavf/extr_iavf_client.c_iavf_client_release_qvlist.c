#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iavf_info {struct iavf_adapter* vf; } ;
struct TYPE_5__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_6__ {TYPE_2__ aq; } ;
struct iavf_adapter {TYPE_3__ hw; TYPE_1__* pdev; scalar_t__ aq_required; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IAVF_SUCCESS ; 
 int /*<<< orphan*/  VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int iavf_aq_send_msg_to_pf (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iavf_client_release_qvlist(struct iavf_info *ldev)
{
	struct iavf_adapter *adapter = ldev->vf;
	enum iavf_status err;

	if (adapter->aq_required)
		return -EAGAIN;

	err = iavf_aq_send_msg_to_pf(&adapter->hw,
				     VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP,
				     IAVF_SUCCESS, NULL, 0, NULL);

	if (err)
		dev_err(&adapter->pdev->dev,
			"Unable to send iWarp vector release message to PF, error %d, aq status %d\n",
			err, adapter->hw.aq.asq_last_status);

	return err;
}