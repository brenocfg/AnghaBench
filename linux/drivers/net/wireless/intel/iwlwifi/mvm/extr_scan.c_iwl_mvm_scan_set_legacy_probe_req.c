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
struct iwl_scan_probe_req_v1 {int /*<<< orphan*/  buf; int /*<<< orphan*/  common_data; int /*<<< orphan*/ * band_data; int /*<<< orphan*/  mac_header; } ;
struct iwl_scan_probe_req {int /*<<< orphan*/  buf; int /*<<< orphan*/  common_data; int /*<<< orphan*/ * band_data; int /*<<< orphan*/  mac_header; } ;

/* Variables and functions */
 int SCAN_NUM_BAND_PROBE_DATA_V_1 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iwl_mvm_scan_set_legacy_probe_req(struct iwl_scan_probe_req_v1 *p_req,
				  struct iwl_scan_probe_req *src_p_req)
{
	int i;

	p_req->mac_header = src_p_req->mac_header;
	for (i = 0; i < SCAN_NUM_BAND_PROBE_DATA_V_1; i++)
		p_req->band_data[i] = src_p_req->band_data[i];
	p_req->common_data = src_p_req->common_data;
	memcpy(p_req->buf, src_p_req->buf, sizeof(p_req->buf));
}