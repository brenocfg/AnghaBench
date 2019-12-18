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
struct intel_hdcp {int /*<<< orphan*/  cp_irq_count; int /*<<< orphan*/  cp_irq_count_cached; } ;
struct intel_dp {int /*<<< orphan*/  aux; TYPE_1__* attached_connector; } ;
struct intel_digital_port {struct intel_dp dp; } ;
struct hdcp2_dp_msg_data {unsigned int offset; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct intel_hdcp hdcp; } ;

/* Variables and functions */
 int DP_AUX_MAX_PAYLOAD_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int drm_dp_dpcd_write (int /*<<< orphan*/ *,unsigned int,void*,int) ; 
 struct hdcp2_dp_msg_data* get_hdcp2_dp_msg_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int intel_dp_hdcp2_write_msg(struct intel_digital_port *intel_dig_port,
			     void *buf, size_t size)
{
	struct intel_dp *dp = &intel_dig_port->dp;
	struct intel_hdcp *hdcp = &dp->attached_connector->hdcp;
	unsigned int offset;
	u8 *byte = buf;
	ssize_t ret, bytes_to_write, len;
	const struct hdcp2_dp_msg_data *hdcp2_msg_data;

	hdcp2_msg_data = get_hdcp2_dp_msg_data(*byte);
	if (!hdcp2_msg_data)
		return -EINVAL;

	offset = hdcp2_msg_data->offset;

	/* No msg_id in DP HDCP2.2 msgs */
	bytes_to_write = size - 1;
	byte++;

	hdcp->cp_irq_count_cached = atomic_read(&hdcp->cp_irq_count);

	while (bytes_to_write) {
		len = bytes_to_write > DP_AUX_MAX_PAYLOAD_BYTES ?
				DP_AUX_MAX_PAYLOAD_BYTES : bytes_to_write;

		ret = drm_dp_dpcd_write(&intel_dig_port->dp.aux,
					offset, (void *)byte, len);
		if (ret < 0)
			return ret;

		bytes_to_write -= ret;
		byte += ret;
		offset += ret;
	}

	return size;
}