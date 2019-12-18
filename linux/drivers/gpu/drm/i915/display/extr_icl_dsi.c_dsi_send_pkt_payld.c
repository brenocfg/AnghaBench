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
struct mipi_dsi_packet {int payload_length; int /*<<< orphan*/  payload; } ;
struct intel_dsi_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int MAX_PLOAD_CREDIT ; 
 int /*<<< orphan*/  add_payld_to_queue (struct intel_dsi_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dsi_send_pkt_payld(struct intel_dsi_host *host,
			      struct mipi_dsi_packet pkt)
{
	/* payload queue can accept *256 bytes*, check limit */
	if (pkt.payload_length > MAX_PLOAD_CREDIT * 4) {
		DRM_ERROR("payload size exceeds max queue limit\n");
		return -1;
	}

	/* load data into command payload queue */
	if (!add_payld_to_queue(host, pkt.payload,
				pkt.payload_length)) {
		DRM_ERROR("adding payload to queue failed\n");
		return -1;
	}

	return 0;
}