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
struct TYPE_2__ {int /*<<< orphan*/  remote_id; int /*<<< orphan*/  local_id; } ;
struct cm_id_private {TYPE_1__ id; int /*<<< orphan*/  tid; } ;
struct cm_drep_msg {int /*<<< orphan*/  private_data; int /*<<< orphan*/  remote_comm_id; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DREP_ATTR_ID ; 
 int /*<<< orphan*/  cm_format_mad_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static void cm_format_drep(struct cm_drep_msg *drep_msg,
			  struct cm_id_private *cm_id_priv,
			  const void *private_data,
			  u8 private_data_len)
{
	cm_format_mad_hdr(&drep_msg->hdr, CM_DREP_ATTR_ID, cm_id_priv->tid);
	drep_msg->local_comm_id = cm_id_priv->id.local_id;
	drep_msg->remote_comm_id = cm_id_priv->id.remote_id;

	if (private_data && private_data_len)
		memcpy(drep_msg->private_data, private_data, private_data_len);
}