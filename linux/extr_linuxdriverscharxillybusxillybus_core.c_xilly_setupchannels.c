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
struct xilly_endpoint {int num_channels; struct device* dev; struct xilly_channel** channels; } ;
struct xilly_channel {int num_wr_buffers; int num_rd_buffers; int wr_fpga_buf_idx; int wr_empty; int wr_sleepy; int chan_num; int log2_element_size; int rd_buf_size; int rd_allow_partial; int rd_synchronous; int rd_exclusive_open; int seekable; int wr_buf_size; int wr_supports_nonempty; int wr_allow_partial; int wr_synchronous; int wr_exclusive_open; struct xilly_buffer** wr_buffers; struct xilly_buffer** rd_buffers; struct xilly_endpoint* endpoint; int /*<<< orphan*/  rd_workitem; int /*<<< orphan*/  wr_ready_wait; int /*<<< orphan*/  wr_wait; int /*<<< orphan*/  rd_wait; int /*<<< orphan*/  rd_mutex; int /*<<< orphan*/  wr_mutex; int /*<<< orphan*/  rd_spinlock; int /*<<< orphan*/  wr_spinlock; scalar_t__ rd_ref_count; scalar_t__ wr_ref_count; scalar_t__ rd_full; scalar_t__ rd_host_buf_pos; scalar_t__ rd_host_buf_idx; scalar_t__ rd_fpga_buf_idx; scalar_t__ wr_ready; scalar_t__ wr_host_buf_pos; scalar_t__ wr_host_buf_idx; } ;
struct xilly_buffer {int dummy; } ;
struct xilly_alloc_state {int nbuffer; int regdirection; int /*<<< orphan*/  direction; int /*<<< orphan*/  left_of_salami; int /*<<< orphan*/ * salami; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int xilly_get_dma_buffers (struct xilly_endpoint*,struct xilly_alloc_state*,struct xilly_buffer**,int,int) ; 
 int /*<<< orphan*/  xillybus_autoflush ; 

__attribute__((used)) static int xilly_setupchannels(struct xilly_endpoint *ep,
			       unsigned char *chandesc,
			       int entries)
{
	struct device *dev = ep->dev;
	int i, entry, rc;
	struct xilly_channel *channel;
	int channelnum, bufnum, bufsize, format, is_writebuf;
	int bytebufsize;
	int synchronous, allowpartial, exclusive_open, seekable;
	int supports_nonempty;
	int msg_buf_done = 0;

	struct xilly_alloc_state rd_alloc = {
		.salami = NULL,
		.left_of_salami = 0,
		.nbuffer = 1,
		.direction = DMA_TO_DEVICE,
		.regdirection = 0,
	};

	struct xilly_alloc_state wr_alloc = {
		.salami = NULL,
		.left_of_salami = 0,
		.nbuffer = 1,
		.direction = DMA_FROM_DEVICE,
		.regdirection = 0x80000000,
	};

	channel = devm_kcalloc(dev, ep->num_channels,
			       sizeof(struct xilly_channel), GFP_KERNEL);
	if (!channel)
		return -ENOMEM;

	ep->channels = devm_kcalloc(dev, ep->num_channels + 1,
				    sizeof(struct xilly_channel *),
				    GFP_KERNEL);
	if (!ep->channels)
		return -ENOMEM;

	ep->channels[0] = NULL; /* Channel 0 is message buf. */

	/* Initialize all channels with defaults */

	for (i = 1; i <= ep->num_channels; i++) {
		channel->wr_buffers = NULL;
		channel->rd_buffers = NULL;
		channel->num_wr_buffers = 0;
		channel->num_rd_buffers = 0;
		channel->wr_fpga_buf_idx = -1;
		channel->wr_host_buf_idx = 0;
		channel->wr_host_buf_pos = 0;
		channel->wr_empty = 1;
		channel->wr_ready = 0;
		channel->wr_sleepy = 1;
		channel->rd_fpga_buf_idx = 0;
		channel->rd_host_buf_idx = 0;
		channel->rd_host_buf_pos = 0;
		channel->rd_full = 0;
		channel->wr_ref_count = 0;
		channel->rd_ref_count = 0;

		spin_lock_init(&channel->wr_spinlock);
		spin_lock_init(&channel->rd_spinlock);
		mutex_init(&channel->wr_mutex);
		mutex_init(&channel->rd_mutex);
		init_waitqueue_head(&channel->rd_wait);
		init_waitqueue_head(&channel->wr_wait);
		init_waitqueue_head(&channel->wr_ready_wait);

		INIT_DELAYED_WORK(&channel->rd_workitem, xillybus_autoflush);

		channel->endpoint = ep;
		channel->chan_num = i;

		channel->log2_element_size = 0;

		ep->channels[i] = channel++;
	}

	for (entry = 0; entry < entries; entry++, chandesc += 4) {
		struct xilly_buffer **buffers = NULL;

		is_writebuf = chandesc[0] & 0x01;
		channelnum = (chandesc[0] >> 1) | ((chandesc[1] & 0x0f) << 7);
		format = (chandesc[1] >> 4) & 0x03;
		allowpartial = (chandesc[1] >> 6) & 0x01;
		synchronous = (chandesc[1] >> 7) & 0x01;
		bufsize = 1 << (chandesc[2] & 0x1f);
		bufnum = 1 << (chandesc[3] & 0x0f);
		exclusive_open = (chandesc[2] >> 7) & 0x01;
		seekable = (chandesc[2] >> 6) & 0x01;
		supports_nonempty = (chandesc[2] >> 5) & 0x01;

		if ((channelnum > ep->num_channels) ||
		    ((channelnum == 0) && !is_writebuf)) {
			dev_err(ep->dev,
				"IDT requests channel out of range. Aborting.\n");
			return -ENODEV;
		}

		channel = ep->channels[channelnum]; /* NULL for msg channel */

		if (!is_writebuf || channelnum > 0) {
			channel->log2_element_size = ((format > 2) ?
						      2 : format);

			bytebufsize = bufsize *
				(1 << channel->log2_element_size);

			buffers = devm_kcalloc(dev, bufnum,
					       sizeof(struct xilly_buffer *),
					       GFP_KERNEL);
			if (!buffers)
				return -ENOMEM;
		} else {
			bytebufsize = bufsize << 2;
		}

		if (!is_writebuf) {
			channel->num_rd_buffers = bufnum;
			channel->rd_buf_size = bytebufsize;
			channel->rd_allow_partial = allowpartial;
			channel->rd_synchronous = synchronous;
			channel->rd_exclusive_open = exclusive_open;
			channel->seekable = seekable;

			channel->rd_buffers = buffers;
			rc = xilly_get_dma_buffers(ep, &rd_alloc, buffers,
						   bufnum, bytebufsize);
		} else if (channelnum > 0) {
			channel->num_wr_buffers = bufnum;
			channel->wr_buf_size = bytebufsize;

			channel->seekable = seekable;
			channel->wr_supports_nonempty = supports_nonempty;

			channel->wr_allow_partial = allowpartial;
			channel->wr_synchronous = synchronous;
			channel->wr_exclusive_open = exclusive_open;

			channel->wr_buffers = buffers;
			rc = xilly_get_dma_buffers(ep, &wr_alloc, buffers,
						   bufnum, bytebufsize);
		} else {
			rc = xilly_get_dma_buffers(ep, &wr_alloc, NULL,
						   bufnum, bytebufsize);
			msg_buf_done++;
		}

		if (rc)
			return -ENOMEM;
	}

	if (!msg_buf_done) {
		dev_err(ep->dev,
			"Corrupt IDT: No message buffer. Aborting.\n");
		return -ENODEV;
	}
	return 0;
}