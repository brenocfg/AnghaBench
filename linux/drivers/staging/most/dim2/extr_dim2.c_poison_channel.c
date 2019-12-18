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
typedef  scalar_t__ u8 ;
struct most_interface {int dummy; } ;
struct hdm_channel {int is_initialized; scalar_t__* reset_dbr_size; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  started_list; int /*<<< orphan*/  name; int /*<<< orphan*/  ch; } ;
struct dim2_hdm {int atx_idx; struct hdm_channel* hch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DIM_NO_ERROR ; 
 int DMA_CHANNELS ; 
 int EFAULT ; 
 int EPERM ; 
 int /*<<< orphan*/  complete_all_mbos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dim2_tasklet ; 
 scalar_t__ dim_destroy_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dim_lock ; 
 struct dim2_hdm* iface_to_hdm (struct most_interface*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int poison_channel(struct most_interface *most_iface, int ch_idx)
{
	struct dim2_hdm *dev = iface_to_hdm(most_iface);
	struct hdm_channel *hdm_ch = dev->hch + ch_idx;
	unsigned long flags;
	u8 hal_ret;
	int ret = 0;

	BUG_ON(ch_idx < 0 || ch_idx >= DMA_CHANNELS);

	if (!hdm_ch->is_initialized)
		return -EPERM;

	tasklet_disable(&dim2_tasklet);
	spin_lock_irqsave(&dim_lock, flags);
	hal_ret = dim_destroy_channel(&hdm_ch->ch);
	hdm_ch->is_initialized = false;
	if (ch_idx == dev->atx_idx)
		dev->atx_idx = -1;
	spin_unlock_irqrestore(&dim_lock, flags);
	tasklet_enable(&dim2_tasklet);
	if (hal_ret != DIM_NO_ERROR) {
		pr_err("HAL Failed to close channel %s\n", hdm_ch->name);
		ret = -EFAULT;
	}

	complete_all_mbos(&hdm_ch->started_list);
	complete_all_mbos(&hdm_ch->pending_list);
	if (hdm_ch->reset_dbr_size)
		*hdm_ch->reset_dbr_size = 0;

	return ret;
}