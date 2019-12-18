#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verify_rxcert_out ;
typedef  int /*<<< orphan*/  verify_rxcert_in ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {scalar_t__ status; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_verify_receiver_cert_out {int /*<<< orphan*/  ekm_buff; scalar_t__ km_stored; TYPE_5__ header; TYPE_2__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  physical_port; int /*<<< orphan*/  integrated_port_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_len; scalar_t__ status; int /*<<< orphan*/  command_id; int /*<<< orphan*/  api_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_verify_receiver_cert_in {int /*<<< orphan*/  rx_caps; int /*<<< orphan*/  r_rx; int /*<<< orphan*/  cert_rx; TYPE_4__ port; TYPE_3__ header; TYPE_1__ member_0; } ;
struct mei_cl_device {int dummy; } ;
struct hdcp_port_data {int /*<<< orphan*/  port; int /*<<< orphan*/  port_type; } ;
struct hdcp2_ake_stored_km {int dummy; } ;
struct hdcp2_ake_send_cert {int /*<<< orphan*/ * rx_caps; int /*<<< orphan*/  r_rx; int /*<<< orphan*/  cert_rx; } ;
struct hdcp2_ake_no_stored_km {int /*<<< orphan*/  e_kpub_km; int /*<<< orphan*/  msg_id; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HDCP_2_2_AKE_NO_STORED_KM ; 
 int /*<<< orphan*/  HDCP_2_2_AKE_STORED_KM ; 
 int HDCP_2_2_RRX_LEN ; 
 int HDCP_2_2_RXCAPS_LEN ; 
 int /*<<< orphan*/  HDCP_API_VERSION ; 
 scalar_t__ ME_HDCP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WIRED_CMD_BUF_LEN_VERIFY_RECEIVER_CERT_IN ; 
 int /*<<< orphan*/  WIRED_VERIFY_RECEIVER_CERT ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,...) ; 
 scalar_t__ mei_cldev_recv (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mei_cldev_send (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mei_get_ddi_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 

__attribute__((used)) static int
mei_hdcp_verify_receiver_cert_prepare_km(struct device *dev,
					 struct hdcp_port_data *data,
					 struct hdcp2_ake_send_cert *rx_cert,
					 bool *km_stored,
					 struct hdcp2_ake_no_stored_km
								*ek_pub_km,
					 size_t *msg_sz)
{
	struct wired_cmd_verify_receiver_cert_in verify_rxcert_in = { { 0 } };
	struct wired_cmd_verify_receiver_cert_out verify_rxcert_out = { { 0 } };
	struct mei_cl_device *cldev;
	ssize_t byte;

	if (!dev || !data || !rx_cert || !km_stored || !ek_pub_km || !msg_sz)
		return -EINVAL;

	cldev = to_mei_cl_device(dev);

	verify_rxcert_in.header.api_version = HDCP_API_VERSION;
	verify_rxcert_in.header.command_id = WIRED_VERIFY_RECEIVER_CERT;
	verify_rxcert_in.header.status = ME_HDCP_STATUS_SUCCESS;
	verify_rxcert_in.header.buffer_len =
				WIRED_CMD_BUF_LEN_VERIFY_RECEIVER_CERT_IN;

	verify_rxcert_in.port.integrated_port_type = data->port_type;
	verify_rxcert_in.port.physical_port = mei_get_ddi_index(data->port);

	verify_rxcert_in.cert_rx = rx_cert->cert_rx;
	memcpy(verify_rxcert_in.r_rx, &rx_cert->r_rx, HDCP_2_2_RRX_LEN);
	memcpy(verify_rxcert_in.rx_caps, rx_cert->rx_caps, HDCP_2_2_RXCAPS_LEN);

	byte = mei_cldev_send(cldev, (u8 *)&verify_rxcert_in,
			      sizeof(verify_rxcert_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_send failed: %zd\n", byte);
		return byte;
	}

	byte = mei_cldev_recv(cldev, (u8 *)&verify_rxcert_out,
			      sizeof(verify_rxcert_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_recv failed: %zd\n", byte);
		return byte;
	}

	if (verify_rxcert_out.header.status != ME_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X Failed. Status: 0x%X\n",
			WIRED_VERIFY_RECEIVER_CERT,
			verify_rxcert_out.header.status);
		return -EIO;
	}

	*km_stored = !!verify_rxcert_out.km_stored;
	if (verify_rxcert_out.km_stored) {
		ek_pub_km->msg_id = HDCP_2_2_AKE_STORED_KM;
		*msg_sz = sizeof(struct hdcp2_ake_stored_km);
	} else {
		ek_pub_km->msg_id = HDCP_2_2_AKE_NO_STORED_KM;
		*msg_sz = sizeof(struct hdcp2_ake_no_stored_km);
	}

	memcpy(ek_pub_km->e_kpub_km, &verify_rxcert_out.ekm_buff,
	       sizeof(verify_rxcert_out.ekm_buff));

	return 0;
}