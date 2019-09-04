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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
struct scmi_xfer {TYPE_2__ rx; TYPE_1__ tx; } ;
struct scmi_handle {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_DISCOVER_LIST_PROTOCOLS ; 
 int MAX_PROTOCOLS_IMP ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_BASE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_base_implementation_list_get(const struct scmi_handle *handle,
					     u8 *protocols_imp)
{
	u8 *list;
	int ret, loop;
	struct scmi_xfer *t;
	__le32 *num_skip, *num_ret;
	u32 tot_num_ret = 0, loop_num_ret;
	struct device *dev = handle->dev;

	ret = scmi_xfer_get_init(handle, BASE_DISCOVER_LIST_PROTOCOLS,
				 SCMI_PROTOCOL_BASE, sizeof(*num_skip), 0, &t);
	if (ret)
		return ret;

	num_skip = t->tx.buf;
	num_ret = t->rx.buf;
	list = t->rx.buf + sizeof(*num_ret);

	do {
		/* Set the number of protocols to be skipped/already read */
		*num_skip = cpu_to_le32(tot_num_ret);

		ret = scmi_do_xfer(handle, t);
		if (ret)
			break;

		loop_num_ret = le32_to_cpu(*num_ret);
		if (tot_num_ret + loop_num_ret > MAX_PROTOCOLS_IMP) {
			dev_err(dev, "No. of Protocol > MAX_PROTOCOLS_IMP");
			break;
		}

		for (loop = 0; loop < loop_num_ret; loop++)
			protocols_imp[tot_num_ret + loop] = *(list + loop);

		tot_num_ret += loop_num_ret;
	} while (loop_num_ret);

	scmi_xfer_put(handle, t);

	return ret;
}