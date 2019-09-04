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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {struct scmi_msg_resp_clock_attributes* buf; } ;
struct TYPE_3__ {scalar_t__ buf; } ;
struct scmi_xfer {TYPE_2__ rx; TYPE_1__ tx; } ;
struct scmi_msg_resp_clock_attributes {int /*<<< orphan*/  name; } ;
struct scmi_handle {int dummy; } ;
struct scmi_clock_info {char* name; } ;
typedef  int /*<<< orphan*/  clk_id ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_ATTRIBUTES ; 
 int /*<<< orphan*/  SCMI_MAX_STR_SIZE ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_CLOCK ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_clock_attributes_get(const struct scmi_handle *handle,
				     u32 clk_id, struct scmi_clock_info *clk)
{
	int ret;
	struct scmi_xfer *t;
	struct scmi_msg_resp_clock_attributes *attr;

	ret = scmi_xfer_get_init(handle, CLOCK_ATTRIBUTES, SCMI_PROTOCOL_CLOCK,
				 sizeof(clk_id), sizeof(*attr), &t);
	if (ret)
		return ret;

	*(__le32 *)t->tx.buf = cpu_to_le32(clk_id);
	attr = t->rx.buf;

	ret = scmi_do_xfer(handle, t);
	if (!ret)
		memcpy(clk->name, attr->name, SCMI_MAX_STR_SIZE);
	else
		clk->name[0] = '\0';

	scmi_xfer_put(handle, t);
	return ret;
}