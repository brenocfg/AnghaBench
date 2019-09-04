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
struct TYPE_3__ {scalar_t__ buf; } ;
struct TYPE_4__ {scalar_t__ buf; } ;
struct scmi_xfer {TYPE_1__ rx; TYPE_2__ tx; } ;
struct scmi_handle {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_STATE_GET ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_POWER ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int
scmi_power_state_get(const struct scmi_handle *handle, u32 domain, u32 *state)
{
	int ret;
	struct scmi_xfer *t;

	ret = scmi_xfer_get_init(handle, POWER_STATE_GET, SCMI_PROTOCOL_POWER,
				 sizeof(u32), sizeof(u32), &t);
	if (ret)
		return ret;

	*(__le32 *)t->tx.buf = cpu_to_le32(domain);

	ret = scmi_do_xfer(handle, t);
	if (!ret)
		*state = le32_to_cpu(*(__le32 *)t->rx.buf);

	scmi_xfer_put(handle, t);
	return ret;
}