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
typedef  void* u8 ;
struct TYPE_2__ {int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct cm_id_private {TYPE_1__ id; int /*<<< orphan*/  tid; } ;
struct cm_apr_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  info; void* info_length; void* ap_status; int /*<<< orphan*/  remote_comm_id; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  hdr; } ;
typedef  enum ib_cm_apr_status { ____Placeholder_ib_cm_apr_status } ib_cm_apr_status ;

/* Variables and functions */
 int /*<<< orphan*/  CM_APR_ATTR_ID ; 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,void*) ; 

__attribute__((used)) static void cm_format_apr(struct cm_apr_msg *apr_msg,
			  struct cm_id_private *cm_id_priv,
			  enum ib_cm_apr_status status,
			  void *info,
			  u8 info_length,
			  const void *private_data,
			  u8 private_data_len)
{
	cm_format_mad_hdr(&apr_msg->hdr, CM_APR_ATTR_ID, cm_id_priv->tid);
	apr_msg->local_comm_id = cm_id_priv->id.local_id;
	apr_msg->remote_comm_id = cm_id_priv->id.remote_id;
	apr_msg->ap_status = (u8) status;

	if (info && info_length) {
		apr_msg->info_length = info_length;
		memcpy(apr_msg->info, info, info_length);
	}

	if (private_data && private_data_len)
		memcpy(apr_msg->private_data, private_data, private_data_len);
}