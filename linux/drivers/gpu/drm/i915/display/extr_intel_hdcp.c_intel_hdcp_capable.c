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
struct intel_hdcp_shim {int /*<<< orphan*/  (* hdcp_capable ) (struct intel_digital_port*,int*) ;} ;
struct intel_digital_port {int dummy; } ;
struct TYPE_2__ {struct intel_hdcp_shim* shim; } ;
struct intel_connector {TYPE_1__ hdcp; } ;

/* Variables and functions */
 struct intel_digital_port* conn_to_dig_port (struct intel_connector*) ; 
 int /*<<< orphan*/  intel_hdcp_read_valid_bksv (struct intel_digital_port*,struct intel_hdcp_shim const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_digital_port*,int*) ; 

bool intel_hdcp_capable(struct intel_connector *connector)
{
	struct intel_digital_port *intel_dig_port = conn_to_dig_port(connector);
	const struct intel_hdcp_shim *shim = connector->hdcp.shim;
	bool capable = false;
	u8 bksv[5];

	if (!shim)
		return capable;

	if (shim->hdcp_capable) {
		shim->hdcp_capable(intel_dig_port, &capable);
	} else {
		if (!intel_hdcp_read_valid_bksv(intel_dig_port, shim, bksv))
			capable = true;
	}

	return capable;
}