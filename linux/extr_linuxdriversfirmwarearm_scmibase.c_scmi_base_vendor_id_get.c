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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct scmi_xfer {TYPE_1__ rx; } ;
struct scmi_revision_info {char* sub_vendor_id; char* vendor_id; } ;
struct scmi_handle {struct scmi_revision_info* version; } ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  BASE_DISCOVER_SUB_VENDOR ; 
 int /*<<< orphan*/  BASE_DISCOVER_VENDOR ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_BASE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int
scmi_base_vendor_id_get(const struct scmi_handle *handle, bool sub_vendor)
{
	u8 cmd;
	int ret, size;
	char *vendor_id;
	struct scmi_xfer *t;
	struct scmi_revision_info *rev = handle->version;

	if (sub_vendor) {
		cmd = BASE_DISCOVER_SUB_VENDOR;
		vendor_id = rev->sub_vendor_id;
		size = ARRAY_SIZE(rev->sub_vendor_id);
	} else {
		cmd = BASE_DISCOVER_VENDOR;
		vendor_id = rev->vendor_id;
		size = ARRAY_SIZE(rev->vendor_id);
	}

	ret = scmi_xfer_get_init(handle, cmd, SCMI_PROTOCOL_BASE, 0, size, &t);
	if (ret)
		return ret;

	ret = scmi_do_xfer(handle, t);
	if (!ret)
		memcpy(vendor_id, t->rx.buf, size);

	scmi_xfer_put(handle, t);

	return ret;
}