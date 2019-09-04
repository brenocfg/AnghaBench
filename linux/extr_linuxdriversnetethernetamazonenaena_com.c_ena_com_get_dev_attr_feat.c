#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ena_com_dev_get_features_ctx {int /*<<< orphan*/  hw_hints; int /*<<< orphan*/  offload; int /*<<< orphan*/  aenq; int /*<<< orphan*/  max_queues; int /*<<< orphan*/  dev_attr; } ;
struct ena_com_dev {int /*<<< orphan*/  tx_max_header_size; int /*<<< orphan*/  supported_features; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_header_size; int /*<<< orphan*/  supported_features; } ;
struct TYPE_3__ {TYPE_2__ hw_hints; TYPE_2__ offload; TYPE_2__ aenq; TYPE_2__ max_queue; TYPE_2__ dev_attr; } ;
struct ena_admin_get_feat_resp {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_AENQ_CONFIG ; 
 int /*<<< orphan*/  ENA_ADMIN_DEVICE_ATTRIBUTES ; 
 int /*<<< orphan*/  ENA_ADMIN_HW_HINTS ; 
 int /*<<< orphan*/  ENA_ADMIN_MAX_QUEUES_NUM ; 
 int /*<<< orphan*/  ENA_ADMIN_STATELESS_OFFLOAD_CONFIG ; 
 int EOPNOTSUPP ; 
 int ena_com_get_feature (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

int ena_com_get_dev_attr_feat(struct ena_com_dev *ena_dev,
			      struct ena_com_dev_get_features_ctx *get_feat_ctx)
{
	struct ena_admin_get_feat_resp get_resp;
	int rc;

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_DEVICE_ATTRIBUTES);
	if (rc)
		return rc;

	memcpy(&get_feat_ctx->dev_attr, &get_resp.u.dev_attr,
	       sizeof(get_resp.u.dev_attr));
	ena_dev->supported_features = get_resp.u.dev_attr.supported_features;

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_MAX_QUEUES_NUM);
	if (rc)
		return rc;

	memcpy(&get_feat_ctx->max_queues, &get_resp.u.max_queue,
	       sizeof(get_resp.u.max_queue));
	ena_dev->tx_max_header_size = get_resp.u.max_queue.max_header_size;

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_AENQ_CONFIG);
	if (rc)
		return rc;

	memcpy(&get_feat_ctx->aenq, &get_resp.u.aenq,
	       sizeof(get_resp.u.aenq));

	rc = ena_com_get_feature(ena_dev, &get_resp,
				 ENA_ADMIN_STATELESS_OFFLOAD_CONFIG);
	if (rc)
		return rc;

	memcpy(&get_feat_ctx->offload, &get_resp.u.offload,
	       sizeof(get_resp.u.offload));

	/* Driver hints isn't mandatory admin command. So in case the
	 * command isn't supported set driver hints to 0
	 */
	rc = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_HW_HINTS);

	if (!rc)
		memcpy(&get_feat_ctx->hw_hints, &get_resp.u.hw_hints,
		       sizeof(get_resp.u.hw_hints));
	else if (rc == -EOPNOTSUPP)
		memset(&get_feat_ctx->hw_hints, 0x0,
		       sizeof(get_feat_ctx->hw_hints));
	else
		return rc;

	return 0;
}