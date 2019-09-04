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
struct TYPE_2__ {struct scmi_msg_resp_base_attributes* buf; } ;
struct scmi_xfer {TYPE_1__ rx; } ;
struct scmi_revision_info {int /*<<< orphan*/  num_agents; int /*<<< orphan*/  num_protocols; } ;
struct scmi_msg_resp_base_attributes {int /*<<< orphan*/  num_agents; int /*<<< orphan*/  num_protocols; } ;
struct scmi_handle {struct scmi_revision_info* version; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_ATTRIBUTES ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_BASE ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_base_attributes_get(const struct scmi_handle *handle)
{
	int ret;
	struct scmi_xfer *t;
	struct scmi_msg_resp_base_attributes *attr_info;
	struct scmi_revision_info *rev = handle->version;

	ret = scmi_xfer_get_init(handle, PROTOCOL_ATTRIBUTES,
				 SCMI_PROTOCOL_BASE, 0, sizeof(*attr_info), &t);
	if (ret)
		return ret;

	ret = scmi_do_xfer(handle, t);
	if (!ret) {
		attr_info = t->rx.buf;
		rev->num_protocols = attr_info->num_protocols;
		rev->num_agents = attr_info->num_agents;
	}

	scmi_xfer_put(handle, t);

	return ret;
}