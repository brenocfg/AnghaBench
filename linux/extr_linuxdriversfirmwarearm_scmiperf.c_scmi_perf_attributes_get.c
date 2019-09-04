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
typedef  int u64 ;
typedef  void* u16 ;
struct TYPE_2__ {struct scmi_msg_resp_perf_attributes* buf; } ;
struct scmi_xfer {TYPE_1__ rx; } ;
struct scmi_perf_info {int stats_addr; int stats_size; int /*<<< orphan*/  power_scale_mw; void* num_domains; } ;
struct scmi_msg_resp_perf_attributes {int /*<<< orphan*/  stats_size; int /*<<< orphan*/  stats_addr_high; int /*<<< orphan*/  stats_addr_low; int /*<<< orphan*/  num_domains; int /*<<< orphan*/  flags; } ;
struct scmi_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SCALE_IN_MILLIWATT (void*) ; 
 int /*<<< orphan*/  PROTOCOL_ATTRIBUTES ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_PERF ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_perf_attributes_get(const struct scmi_handle *handle,
				    struct scmi_perf_info *pi)
{
	int ret;
	struct scmi_xfer *t;
	struct scmi_msg_resp_perf_attributes *attr;

	ret = scmi_xfer_get_init(handle, PROTOCOL_ATTRIBUTES,
				 SCMI_PROTOCOL_PERF, 0, sizeof(*attr), &t);
	if (ret)
		return ret;

	attr = t->rx.buf;

	ret = scmi_do_xfer(handle, t);
	if (!ret) {
		u16 flags = le16_to_cpu(attr->flags);

		pi->num_domains = le16_to_cpu(attr->num_domains);
		pi->power_scale_mw = POWER_SCALE_IN_MILLIWATT(flags);
		pi->stats_addr = le32_to_cpu(attr->stats_addr_low) |
				(u64)le32_to_cpu(attr->stats_addr_high) << 32;
		pi->stats_size = le32_to_cpu(attr->stats_size);
	}

	scmi_xfer_put(handle, t);
	return ret;
}