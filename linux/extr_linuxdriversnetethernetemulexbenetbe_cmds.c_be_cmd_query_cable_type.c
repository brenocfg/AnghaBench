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
typedef  void* u8 ;
struct TYPE_2__ {int interface_type; void* cable_type; } ;
struct be_adapter {TYPE_1__ phy; } ;

/* Variables and functions */
 int PAGE_DATA_LEN ; 
#define  PHY_TYPE_QSFP 129 
#define  PHY_TYPE_SFP_PLUS_10GB 128 
 size_t QSFP_PLUS_CABLE_TYPE_OFFSET ; 
 size_t SFP_PLUS_CABLE_TYPE_OFFSET ; 
 int /*<<< orphan*/  TR_PAGE_A0 ; 
 int be_cmd_read_port_transceiver_data (struct be_adapter*,int /*<<< orphan*/ ,void**) ; 

int be_cmd_query_cable_type(struct be_adapter *adapter)
{
	u8 page_data[PAGE_DATA_LEN];
	int status;

	status = be_cmd_read_port_transceiver_data(adapter, TR_PAGE_A0,
						   page_data);
	if (!status) {
		switch (adapter->phy.interface_type) {
		case PHY_TYPE_QSFP:
			adapter->phy.cable_type =
				page_data[QSFP_PLUS_CABLE_TYPE_OFFSET];
			break;
		case PHY_TYPE_SFP_PLUS_10GB:
			adapter->phy.cable_type =
				page_data[SFP_PLUS_CABLE_TYPE_OFFSET];
			break;
		default:
			adapter->phy.cable_type = 0;
			break;
		}
	}
	return status;
}