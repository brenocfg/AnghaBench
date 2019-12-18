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
struct drm_dp_aux {int dummy; } ;
struct TYPE_2__ {int log_addr_mask; } ;
struct cec_adapter {TYPE_1__ log_addrs; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int CEC_LOG_ADDR_BROADCAST ; 
 int CEC_LOG_ADDR_INVALID ; 
 int /*<<< orphan*/  DP_CEC_LOGICAL_ADDRESS_MASK ; 
 struct drm_dp_aux* cec_get_drvdata (struct cec_adapter*) ; 
 scalar_t__ drm_dp_dpcd_write (struct drm_dp_aux*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int drm_dp_cec_adap_log_addr(struct cec_adapter *adap, u8 addr)
{
	struct drm_dp_aux *aux = cec_get_drvdata(adap);
	/* Bit 15 (logical address 15) should always be set */
	u16 la_mask = 1 << CEC_LOG_ADDR_BROADCAST;
	u8 mask[2];
	ssize_t err;

	if (addr != CEC_LOG_ADDR_INVALID)
		la_mask |= adap->log_addrs.log_addr_mask | (1 << addr);
	mask[0] = la_mask & 0xff;
	mask[1] = la_mask >> 8;
	err = drm_dp_dpcd_write(aux, DP_CEC_LOGICAL_ADDRESS_MASK, mask, 2);
	return (addr != CEC_LOG_ADDR_INVALID && err < 0) ? err : 0;
}