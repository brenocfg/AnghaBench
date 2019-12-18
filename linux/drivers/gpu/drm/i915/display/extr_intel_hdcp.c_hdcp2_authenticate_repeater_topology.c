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
typedef  scalar_t__ u32 ;
struct intel_hdcp_shim {int (* read_2_2_msg ) (struct intel_digital_port*,int /*<<< orphan*/ ,struct hdcp2_rep_send_receiverid_list*,int) ;int (* write_2_2_msg ) (struct intel_digital_port*,struct hdcp2_rep_send_ack*,int) ;} ;
struct intel_hdcp {scalar_t__ seq_num_v; struct intel_hdcp_shim* shim; } ;
struct intel_digital_port {int dummy; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_connector {TYPE_1__ base; struct intel_hdcp hdcp; } ;
struct hdcp2_rep_send_receiverid_list {int /*<<< orphan*/  receiver_ids; scalar_t__ seq_num_v; int /*<<< orphan*/ * rx_info; } ;
struct hdcp2_rep_send_ack {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int EPERM ; 
 int HDCP_2_2_DEV_COUNT_HI (int /*<<< orphan*/ ) ; 
 int HDCP_2_2_DEV_COUNT_LO (int /*<<< orphan*/ ) ; 
 scalar_t__ HDCP_2_2_MAX_CASCADE_EXCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ HDCP_2_2_MAX_DEVS_EXCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDCP_2_2_REP_SEND_RECVID_LIST ; 
 struct intel_digital_port* conn_to_dig_port (struct intel_connector*) ; 
 scalar_t__ drm_hdcp_be24_to_cpu (int /*<<< orphan*/  const*) ; 
 scalar_t__ drm_hdcp_check_ksvs_revoked (struct drm_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int hdcp2_verify_rep_topology_prepare_ack (struct intel_connector*,struct hdcp2_rep_send_receiverid_list*,struct hdcp2_rep_send_ack*) ; 
 int stub1 (struct intel_digital_port*,int /*<<< orphan*/ ,struct hdcp2_rep_send_receiverid_list*,int) ; 
 int stub2 (struct intel_digital_port*,struct hdcp2_rep_send_ack*,int) ; 

__attribute__((used)) static
int hdcp2_authenticate_repeater_topology(struct intel_connector *connector)
{
	struct intel_digital_port *intel_dig_port = conn_to_dig_port(connector);
	struct intel_hdcp *hdcp = &connector->hdcp;
	struct drm_device *dev = connector->base.dev;
	union {
		struct hdcp2_rep_send_receiverid_list recvid_list;
		struct hdcp2_rep_send_ack rep_ack;
	} msgs;
	const struct intel_hdcp_shim *shim = hdcp->shim;
	u32 seq_num_v, device_cnt;
	u8 *rx_info;
	int ret;

	ret = shim->read_2_2_msg(intel_dig_port, HDCP_2_2_REP_SEND_RECVID_LIST,
				 &msgs.recvid_list, sizeof(msgs.recvid_list));
	if (ret < 0)
		return ret;

	rx_info = msgs.recvid_list.rx_info;

	if (HDCP_2_2_MAX_CASCADE_EXCEEDED(rx_info[1]) ||
	    HDCP_2_2_MAX_DEVS_EXCEEDED(rx_info[1])) {
		DRM_DEBUG_KMS("Topology Max Size Exceeded\n");
		return -EINVAL;
	}

	/* Converting and Storing the seq_num_v to local variable as DWORD */
	seq_num_v =
		drm_hdcp_be24_to_cpu((const u8 *)msgs.recvid_list.seq_num_v);

	if (seq_num_v < hdcp->seq_num_v) {
		/* Roll over of the seq_num_v from repeater. Reauthenticate. */
		DRM_DEBUG_KMS("Seq_num_v roll over.\n");
		return -EINVAL;
	}

	device_cnt = (HDCP_2_2_DEV_COUNT_HI(rx_info[0]) << 4 |
		      HDCP_2_2_DEV_COUNT_LO(rx_info[1]));
	if (drm_hdcp_check_ksvs_revoked(dev, msgs.recvid_list.receiver_ids,
					device_cnt)) {
		DRM_ERROR("Revoked receiver ID(s) is in list\n");
		return -EPERM;
	}

	ret = hdcp2_verify_rep_topology_prepare_ack(connector,
						    &msgs.recvid_list,
						    &msgs.rep_ack);
	if (ret < 0)
		return ret;

	hdcp->seq_num_v = seq_num_v;
	ret = shim->write_2_2_msg(intel_dig_port, &msgs.rep_ack,
				  sizeof(msgs.rep_ack));
	if (ret < 0)
		return ret;

	return 0;
}