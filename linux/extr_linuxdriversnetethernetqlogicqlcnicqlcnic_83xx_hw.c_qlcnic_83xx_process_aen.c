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
struct qlcnic_mailbox {int rsp_status; int /*<<< orphan*/  aen_lock; } ;
struct qlcnic_hardware_context {struct qlcnic_mailbox* mailbox; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FW_MBX_CTRL ; 
 int QLCNIC_MBX_ASYNC_EVENT ; 
 int /*<<< orphan*/  QLCNIC_MBX_FW (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int QLCNIC_SET_OWNER ; 
 int QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int QLC_83XX_MBX_RESPONSE_ARRIVED ; 
 int /*<<< orphan*/  __qlcnic_83xx_process_aen (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_notify_mbx_response (struct qlcnic_mailbox*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qlcnic_83xx_process_aen(struct qlcnic_adapter *adapter)
{
	u32 resp, event, rsp_status = QLC_83XX_MBX_RESPONSE_ARRIVED;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_mailbox *mbx = ahw->mailbox;
	unsigned long flags;

	spin_lock_irqsave(&mbx->aen_lock, flags);
	resp = QLCRDX(ahw, QLCNIC_FW_MBX_CTRL);
	if (resp & QLCNIC_SET_OWNER) {
		event = readl(QLCNIC_MBX_FW(ahw, 0));
		if (event &  QLCNIC_MBX_ASYNC_EVENT) {
			__qlcnic_83xx_process_aen(adapter);
		} else {
			if (mbx->rsp_status != rsp_status)
				qlcnic_83xx_notify_mbx_response(mbx);
		}
	}
	spin_unlock_irqrestore(&mbx->aen_lock, flags);
}