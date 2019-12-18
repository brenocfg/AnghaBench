#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int error; int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ sec; } ;
struct dmxdev_filter {scalar_t__ state; TYPE_4__ buffer; TYPE_3__* dev; TYPE_2__ params; int /*<<< orphan*/  vb2_ctx; int /*<<< orphan*/  timer; } ;
struct dmx_section_filter {struct dmxdev_filter* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ DMXDEV_STATE_DONE ; 
 scalar_t__ DMXDEV_STATE_GO ; 
 int DMX_ONESHOT ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/  const*) ; 
 int dvb_dmxdev_buffer_write (TYPE_4__*,int /*<<< orphan*/  const*,size_t) ; 
 int dvb_vb2_fill_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ dvb_vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_dmxdev_section_callback(const u8 *buffer1, size_t buffer1_len,
				       const u8 *buffer2, size_t buffer2_len,
				       struct dmx_section_filter *filter,
				       u32 *buffer_flags)
{
	struct dmxdev_filter *dmxdevfilter = filter->priv;
	int ret;

	if (!dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx) &&
	    dmxdevfilter->buffer.error) {
		wake_up(&dmxdevfilter->buffer.queue);
		return 0;
	}
	spin_lock(&dmxdevfilter->dev->lock);
	if (dmxdevfilter->state != DMXDEV_STATE_GO) {
		spin_unlock(&dmxdevfilter->dev->lock);
		return 0;
	}
	del_timer(&dmxdevfilter->timer);
	dprintk("section callback %*ph\n", 6, buffer1);
	if (dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx)) {
		ret = dvb_vb2_fill_buffer(&dmxdevfilter->vb2_ctx,
					  buffer1, buffer1_len,
					  buffer_flags);
		if (ret == buffer1_len)
			ret = dvb_vb2_fill_buffer(&dmxdevfilter->vb2_ctx,
						  buffer2, buffer2_len,
						  buffer_flags);
	} else {
		ret = dvb_dmxdev_buffer_write(&dmxdevfilter->buffer,
					      buffer1, buffer1_len);
		if (ret == buffer1_len) {
			ret = dvb_dmxdev_buffer_write(&dmxdevfilter->buffer,
						      buffer2, buffer2_len);
		}
	}
	if (ret < 0)
		dmxdevfilter->buffer.error = ret;
	if (dmxdevfilter->params.sec.flags & DMX_ONESHOT)
		dmxdevfilter->state = DMXDEV_STATE_DONE;
	spin_unlock(&dmxdevfilter->dev->lock);
	wake_up(&dmxdevfilter->buffer.queue);
	return 0;
}