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
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
union hdmi_scdc_status_flags_data {int* byte; TYPE_1__ member_0; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  tmds_config ;
struct ddc_service {int dummy; } ;
typedef  int /*<<< orphan*/  scramble_status ;
typedef  int /*<<< orphan*/  offset ;

/* Variables and functions */
 int HDMI_SCDC_ADDRESS ; 
 int HDMI_SCDC_SCRAMBLER_STATUS ; 
 int HDMI_SCDC_STATUS_FLAGS ; 
 int HDMI_SCDC_TMDS_CONFIG ; 
 int /*<<< orphan*/  dal_ddc_service_query_ddc_data (struct ddc_service*,int,int*,int,int*,int) ; 

void dal_ddc_service_read_scdc_data(struct ddc_service *ddc_service)
{
	uint8_t slave_address = HDMI_SCDC_ADDRESS;
	uint8_t offset = HDMI_SCDC_TMDS_CONFIG;
	uint8_t tmds_config = 0;

	dal_ddc_service_query_ddc_data(ddc_service, slave_address, &offset,
			sizeof(offset), &tmds_config, sizeof(tmds_config));
	if (tmds_config & 0x1) {
		union hdmi_scdc_status_flags_data status_data = { {0} };
		uint8_t scramble_status = 0;

		offset = HDMI_SCDC_SCRAMBLER_STATUS;
		dal_ddc_service_query_ddc_data(ddc_service, slave_address,
				&offset, sizeof(offset), &scramble_status,
				sizeof(scramble_status));
		offset = HDMI_SCDC_STATUS_FLAGS;
		dal_ddc_service_query_ddc_data(ddc_service, slave_address,
				&offset, sizeof(offset), status_data.byte,
				sizeof(status_data.byte));
	}
}