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
struct xilly_channel {scalar_t__ rd_ref_count; int chan_num; scalar_t__ wr_ref_count; int wr_fpga_buf_idx; int wr_eof; int wr_sleepy; int num_wr_buffers; int /*<<< orphan*/  wr_mutex; TYPE_1__* endpoint; int /*<<< orphan*/  wr_wait; int /*<<< orphan*/  wr_spinlock; int /*<<< orphan*/  rd_mutex; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct xilly_channel* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ registers; scalar_t__ fatal_error; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fpga_buf_ctrl_reg ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xillybus_release(struct inode *inode, struct file *filp)
{
	unsigned long flags;
	struct xilly_channel *channel = filp->private_data;

	int buf_idx;
	int eof;

	if (channel->endpoint->fatal_error)
		return -EIO;

	if (filp->f_mode & FMODE_WRITE) {
		mutex_lock(&channel->rd_mutex);

		channel->rd_ref_count--;

		if (channel->rd_ref_count == 0) {
			/*
			 * We rely on the kernel calling flush()
			 * before we get here.
			 */

			iowrite32((channel->chan_num << 1) | /* Channel ID */
				  (5 << 24),  /* Opcode 5, close channel */
				  channel->endpoint->registers +
				  fpga_buf_ctrl_reg);
		}
		mutex_unlock(&channel->rd_mutex);
	}

	if (filp->f_mode & FMODE_READ) {
		mutex_lock(&channel->wr_mutex);

		channel->wr_ref_count--;

		if (channel->wr_ref_count == 0) {
			iowrite32(1 | (channel->chan_num << 1) |
				  (5 << 24),  /* Opcode 5, close channel */
				  channel->endpoint->registers +
				  fpga_buf_ctrl_reg);

			/*
			 * This is crazily cautious: We make sure that not
			 * only that we got an EOF (be it because we closed
			 * the channel or because of a user's EOF), but verify
			 * that it's one beyond the last buffer arrived, so
			 * we have no leftover buffers pending before wrapping
			 * up (which can only happen in asynchronous channels,
			 * BTW)
			 */

			while (1) {
				spin_lock_irqsave(&channel->wr_spinlock,
						  flags);
				buf_idx = channel->wr_fpga_buf_idx;
				eof = channel->wr_eof;
				channel->wr_sleepy = 1;
				spin_unlock_irqrestore(&channel->wr_spinlock,
						       flags);

				/*
				 * Check if eof points at the buffer after
				 * the last one the FPGA submitted. Note that
				 * no EOF is marked by negative eof.
				 */

				buf_idx++;
				if (buf_idx == channel->num_wr_buffers)
					buf_idx = 0;

				if (buf_idx == eof)
					break;

				/*
				 * Steal extra 100 ms if awaken by interrupt.
				 * This is a simple workaround for an
				 * interrupt pending when entering, which would
				 * otherwise result in declaring the hardware
				 * non-responsive.
				 */

				if (wait_event_interruptible(
					    channel->wr_wait,
					    (!channel->wr_sleepy)))
					msleep(100);

				if (channel->wr_sleepy) {
					mutex_unlock(&channel->wr_mutex);
					dev_warn(channel->endpoint->dev,
						 "Hardware failed to respond to close command, therefore left in messy state.\n");
					return -EINTR;
				}
			}
		}

		mutex_unlock(&channel->wr_mutex);
	}

	return 0;
}