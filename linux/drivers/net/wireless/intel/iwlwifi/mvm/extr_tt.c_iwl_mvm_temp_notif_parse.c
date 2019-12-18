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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_dts_measurement_notif_v1 {int /*<<< orphan*/  temp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_temp_notif_parse(struct iwl_mvm *mvm,
				    struct iwl_rx_packet *pkt)
{
	struct iwl_dts_measurement_notif_v1 *notif_v1;
	int len = iwl_rx_packet_payload_len(pkt);
	int temp;

	/* we can use notif_v1 only, because v2 only adds an additional
	 * parameter, which is not used in this function.
	*/
	if (WARN_ON_ONCE(len < sizeof(*notif_v1))) {
		IWL_ERR(mvm, "Invalid DTS_MEASUREMENT_NOTIFICATION\n");
		return -EINVAL;
	}

	notif_v1 = (void *)pkt->data;

	temp = le32_to_cpu(notif_v1->temp);

	/* shouldn't be negative, but since it's s32, make sure it isn't */
	if (WARN_ON_ONCE(temp < 0))
		temp = 0;

	IWL_DEBUG_TEMP(mvm, "DTS_MEASUREMENT_NOTIFICATION - %d\n", temp);

	return temp;
}