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
typedef  scalar_t__ u8 ;
struct cm_mra_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  remote_comm_id; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct cm_id_private {TYPE_1__ id; int /*<<< orphan*/  tid; } ;
typedef  enum cm_msg_response { ____Placeholder_cm_msg_response } cm_msg_response ;

/* Variables and functions */
 int /*<<< orphan*/  CM_MRA_ATTR_ID ; 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_mra_set_msg_mraed (struct cm_mra_msg*,int) ; 
 int /*<<< orphan*/  cm_mra_set_service_timeout (struct cm_mra_msg*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static void cm_format_mra(struct cm_mra_msg *mra_msg,
			  struct cm_id_private *cm_id_priv,
			  enum cm_msg_response msg_mraed, u8 service_timeout,
			  const void *private_data, u8 private_data_len)
{
	cm_format_mad_hdr(&mra_msg->hdr, CM_MRA_ATTR_ID, cm_id_priv->tid);
	cm_mra_set_msg_mraed(mra_msg, msg_mraed);
	mra_msg->local_comm_id = cm_id_priv->id.local_id;
	mra_msg->remote_comm_id = cm_id_priv->id.remote_id;
	cm_mra_set_service_timeout(mra_msg, service_timeout);

	if (private_data && private_data_len)
		memcpy(mra_msg->private_data, private_data, private_data_len);
}