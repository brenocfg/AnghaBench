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
typedef  int u32 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_BUF_CTL (int /*<<< orphan*/ ) ; 
 int DDI_BUF_CTL_ENABLE ; 
 int /*<<< orphan*/  DP_TP_CTL (int /*<<< orphan*/ ) ; 
 int DP_TP_CTL_ENABLE ; 
 int DP_TP_CTL_FDI_AUTOTRAIN ; 
 int FDI_AUTO_TRAINING ; 
 int FDI_RX_ENABLE ; 
 int /*<<< orphan*/  PORT_E ; 
 int /*<<< orphan*/  _FDI_RXA_CTL ; 
 int vgpu_vreg (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int vgpu_vreg_t (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdi_auto_training_started(struct intel_vgpu *vgpu)
{
	u32 ddi_buf_ctl = vgpu_vreg_t(vgpu, DDI_BUF_CTL(PORT_E));
	u32 rx_ctl = vgpu_vreg(vgpu, _FDI_RXA_CTL);
	u32 tx_ctl = vgpu_vreg_t(vgpu, DP_TP_CTL(PORT_E));

	if ((ddi_buf_ctl & DDI_BUF_CTL_ENABLE) &&
			(rx_ctl & FDI_RX_ENABLE) &&
			(rx_ctl & FDI_AUTO_TRAINING) &&
			(tx_ctl & DP_TP_CTL_ENABLE) &&
			(tx_ctl & DP_TP_CTL_FDI_AUTOTRAIN))
		return 1;
	else
		return 0;
}