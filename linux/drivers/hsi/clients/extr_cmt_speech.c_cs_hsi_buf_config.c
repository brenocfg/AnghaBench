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
struct cs_hsi_iface {unsigned int iface_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  pm_qos_req; scalar_t__ buf_size; scalar_t__ slot_size; scalar_t__ tx_slot; scalar_t__ rx_slot; int /*<<< orphan*/  flags; TYPE_1__* mmap_cfg; int /*<<< orphan*/  data_state; } ;
struct cs_buffer_config {int /*<<< orphan*/  flags; scalar_t__ buf_size; } ;
struct TYPE_2__ {scalar_t__ buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_QOS_LATENCY_FOR_DATA_USEC ; 
 unsigned int CS_STATE_CONFIGURED ; 
 unsigned int CS_STATE_OPENED ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int check_buf_params (struct cs_hsi_iface*,struct cs_buffer_config*) ; 
 int /*<<< orphan*/  cs_hsi_data_disable (struct cs_hsi_iface*,unsigned int) ; 
 int /*<<< orphan*/  cs_hsi_data_enable (struct cs_hsi_iface*,struct cs_buffer_config*) ; 
 int cs_hsi_data_sync (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_hsi_read_on_data (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_state_xfer_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs_hsi_buf_config(struct cs_hsi_iface *hi,
					struct cs_buffer_config *buf_cfg)
{
	int r = 0;
	unsigned int old_state = hi->iface_state;

	spin_lock_bh(&hi->lock);
	/* Prevent new transactions during buffer reconfig */
	if (old_state == CS_STATE_CONFIGURED)
		hi->iface_state = CS_STATE_OPENED;
	spin_unlock_bh(&hi->lock);

	/*
	 * make sure that no non-zero data reads are ongoing before
	 * proceeding to change the buffer layout
	 */
	r = cs_hsi_data_sync(hi);
	if (r < 0)
		return r;

	WARN_ON(cs_state_xfer_active(hi->data_state));

	spin_lock_bh(&hi->lock);
	r = check_buf_params(hi, buf_cfg);
	if (r < 0)
		goto error;

	hi->buf_size = buf_cfg->buf_size;
	hi->mmap_cfg->buf_size = hi->buf_size;
	hi->flags = buf_cfg->flags;

	hi->rx_slot = 0;
	hi->tx_slot = 0;
	hi->slot_size = 0;

	if (hi->buf_size)
		cs_hsi_data_enable(hi, buf_cfg);
	else
		cs_hsi_data_disable(hi, old_state);

	spin_unlock_bh(&hi->lock);

	if (old_state != hi->iface_state) {
		if (hi->iface_state == CS_STATE_CONFIGURED) {
			pm_qos_add_request(&hi->pm_qos_req,
				PM_QOS_CPU_DMA_LATENCY,
				CS_QOS_LATENCY_FOR_DATA_USEC);
			local_bh_disable();
			cs_hsi_read_on_data(hi);
			local_bh_enable();
		} else if (old_state == CS_STATE_CONFIGURED) {
			pm_qos_remove_request(&hi->pm_qos_req);
		}
	}
	return r;

error:
	spin_unlock_bh(&hi->lock);
	return r;
}