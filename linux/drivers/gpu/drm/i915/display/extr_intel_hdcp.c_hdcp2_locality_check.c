#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_hdcp_shim {int (* write_2_2_msg ) (struct intel_digital_port*,struct hdcp2_lc_init*,int) ;int (* read_2_2_msg ) (struct intel_digital_port*,int /*<<< orphan*/ ,struct hdcp2_lc_send_lprime*,int) ;} ;
struct intel_hdcp {struct intel_hdcp_shim* shim; } ;
struct intel_digital_port {int dummy; } ;
struct intel_connector {struct intel_hdcp hdcp; } ;
struct hdcp2_lc_send_lprime {int dummy; } ;
struct hdcp2_lc_init {int dummy; } ;

/* Variables and functions */
 int HDCP2_LC_RETRY_CNT ; 
 int /*<<< orphan*/  HDCP_2_2_LC_SEND_LPRIME ; 
 struct intel_digital_port* conn_to_dig_port (struct intel_connector*) ; 
 int hdcp2_prepare_lc_init (struct intel_connector*,struct hdcp2_lc_init*) ; 
 int hdcp2_verify_lprime (struct intel_connector*,struct hdcp2_lc_send_lprime*) ; 
 int stub1 (struct intel_digital_port*,struct hdcp2_lc_init*,int) ; 
 int stub2 (struct intel_digital_port*,int /*<<< orphan*/ ,struct hdcp2_lc_send_lprime*,int) ; 

__attribute__((used)) static int hdcp2_locality_check(struct intel_connector *connector)
{
	struct intel_digital_port *intel_dig_port = conn_to_dig_port(connector);
	struct intel_hdcp *hdcp = &connector->hdcp;
	union {
		struct hdcp2_lc_init lc_init;
		struct hdcp2_lc_send_lprime send_lprime;
	} msgs;
	const struct intel_hdcp_shim *shim = hdcp->shim;
	int tries = HDCP2_LC_RETRY_CNT, ret, i;

	for (i = 0; i < tries; i++) {
		ret = hdcp2_prepare_lc_init(connector, &msgs.lc_init);
		if (ret < 0)
			continue;

		ret = shim->write_2_2_msg(intel_dig_port, &msgs.lc_init,
				      sizeof(msgs.lc_init));
		if (ret < 0)
			continue;

		ret = shim->read_2_2_msg(intel_dig_port,
					 HDCP_2_2_LC_SEND_LPRIME,
					 &msgs.send_lprime,
					 sizeof(msgs.send_lprime));
		if (ret < 0)
			continue;

		ret = hdcp2_verify_lprime(connector, &msgs.send_lprime);
		if (!ret)
			break;
	}

	return ret;
}