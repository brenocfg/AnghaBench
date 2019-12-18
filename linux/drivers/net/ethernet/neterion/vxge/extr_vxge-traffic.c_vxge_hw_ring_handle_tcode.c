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
typedef  size_t u8 ;
struct __vxge_hw_ring {TYPE_1__* stats; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_2__ {int /*<<< orphan*/ * rxd_t_code_err_cnt; } ;

/* Variables and functions */
 int VXGE_HW_ERR_INVALID_TCODE ; 
 int VXGE_HW_OK ; 
 size_t VXGE_HW_RING_T_CODE_L3_PKT_ERR ; 
 size_t VXGE_HW_RING_T_CODE_MULTI_ERR ; 
 size_t VXGE_HW_RING_T_CODE_OK ; 

enum vxge_hw_status vxge_hw_ring_handle_tcode(
	struct __vxge_hw_ring *ring, void *rxdh, u8 t_code)
{
	enum vxge_hw_status status = VXGE_HW_OK;

	/* If the t_code is not supported and if the
	 * t_code is other than 0x5 (unparseable packet
	 * such as unknown UPV6 header), Drop it !!!
	 */

	if (t_code ==  VXGE_HW_RING_T_CODE_OK ||
		t_code == VXGE_HW_RING_T_CODE_L3_PKT_ERR) {
		status = VXGE_HW_OK;
		goto exit;
	}

	if (t_code > VXGE_HW_RING_T_CODE_MULTI_ERR) {
		status = VXGE_HW_ERR_INVALID_TCODE;
		goto exit;
	}

	ring->stats->rxd_t_code_err_cnt[t_code]++;
exit:
	return status;
}