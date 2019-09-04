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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ sq_last_status; } ;
struct ice_hw {TYPE_1__ adminq; } ;
struct ice_aqc_list_caps_elem {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ICE_AQ_RC_ENOMEM ; 
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,void*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_discover_caps (struct ice_hw*,void*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_aqc_opc_list_func_caps ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

enum ice_status ice_get_caps(struct ice_hw *hw)
{
	enum ice_status status;
	u16 data_size = 0;
	u16 cbuf_len;
	u8 retries;

	/* The driver doesn't know how many capabilities the device will return
	 * so the buffer size required isn't known ahead of time. The driver
	 * starts with cbuf_len and if this turns out to be insufficient, the
	 * device returns ICE_AQ_RC_ENOMEM and also the buffer size it needs.
	 * The driver then allocates the buffer of this size and retries the
	 * operation. So it follows that the retry count is 2.
	 */
#define ICE_GET_CAP_BUF_COUNT	40
#define ICE_GET_CAP_RETRY_COUNT	2

	cbuf_len = ICE_GET_CAP_BUF_COUNT *
		sizeof(struct ice_aqc_list_caps_elem);

	retries = ICE_GET_CAP_RETRY_COUNT;

	do {
		void *cbuf;

		cbuf = devm_kzalloc(ice_hw_to_dev(hw), cbuf_len, GFP_KERNEL);
		if (!cbuf)
			return ICE_ERR_NO_MEMORY;

		status = ice_aq_discover_caps(hw, cbuf, cbuf_len, &data_size,
					      ice_aqc_opc_list_func_caps, NULL);
		devm_kfree(ice_hw_to_dev(hw), cbuf);

		if (!status || hw->adminq.sq_last_status != ICE_AQ_RC_ENOMEM)
			break;

		/* If ENOMEM is returned, try again with bigger buffer */
		cbuf_len = data_size;
	} while (--retries);

	return status;
}