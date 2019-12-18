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
struct ib_cm_sidr_req_param {scalar_t__ private_data_len; scalar_t__ private_data; int /*<<< orphan*/  service_id; TYPE_1__* path; } ;
struct cm_sidr_req_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  service_id; int /*<<< orphan*/  pkey; int /*<<< orphan*/  request_id; int /*<<< orphan*/  hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_id; } ;
struct cm_id_private {TYPE_2__ id; } ;
struct TYPE_3__ {int /*<<< orphan*/  pkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_SIDR_REQ_ATTR_ID ; 
 int /*<<< orphan*/  cm_form_tid (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void cm_format_sidr_req(struct cm_sidr_req_msg *sidr_req_msg,
			       struct cm_id_private *cm_id_priv,
			       struct ib_cm_sidr_req_param *param)
{
	cm_format_mad_hdr(&sidr_req_msg->hdr, CM_SIDR_REQ_ATTR_ID,
			  cm_form_tid(cm_id_priv));
	sidr_req_msg->request_id = cm_id_priv->id.local_id;
	sidr_req_msg->pkey = param->path->pkey;
	sidr_req_msg->service_id = param->service_id;

	if (param->private_data && param->private_data_len)
		memcpy(sidr_req_msg->private_data, param->private_data,
		       param->private_data_len);
}