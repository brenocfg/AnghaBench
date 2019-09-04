#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_8__ {int crc_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  rxok; int /*<<< orphan*/  rxlong; int /*<<< orphan*/  rxcrc; int /*<<< orphan*/  rxover; int /*<<< orphan*/  rxabort; } ;
struct TYPE_10__ {scalar_t__ rx_frame_count; int rx_get; int rx_buf_size; unsigned int max_frame_size; int rx_buf_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  flag_buf; TYPE_2__ params; TYPE_1__ icount; int /*<<< orphan*/  device_name; scalar_t__ rx_buf; } ;
struct TYPE_9__ {unsigned short status; unsigned int count; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ RXBUF ;
typedef  TYPE_4__ MGSLPC_INFO ;

/* Variables and functions */
 unsigned short BIT4 ; 
 unsigned short BIT5 ; 
 unsigned short BIT6 ; 
 unsigned short BIT7 ; 
 scalar_t__ DEBUG_LEVEL_BH ; 
 scalar_t__ DEBUG_LEVEL_DATA ; 
 int HDLC_CRC_RETURN_EX ; 
 int /*<<< orphan*/  RX_CRC_ERROR ; 
 int /*<<< orphan*/  RX_OK ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  ldisc_receive_buf (struct tty_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned short,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_block (TYPE_4__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rx_get_frame(MGSLPC_INFO *info, struct tty_struct *tty)
{
	unsigned short status;
	RXBUF *buf;
	unsigned int framesize = 0;
	unsigned long flags;
	bool return_frame = false;

	if (info->rx_frame_count == 0)
		return false;

	buf = (RXBUF*)(info->rx_buf + (info->rx_get * info->rx_buf_size));

	status = buf->status;

	/* 07  VFR  1=valid frame
	 * 06  RDO  1=data overrun
	 * 05  CRC  1=OK, 0=error
	 * 04  RAB  1=frame aborted
	 */
	if ((status & 0xf0) != 0xA0) {
		if (!(status & BIT7) || (status & BIT4))
			info->icount.rxabort++;
		else if (status & BIT6)
			info->icount.rxover++;
		else if (!(status & BIT5)) {
			info->icount.rxcrc++;
			if (info->params.crc_type & HDLC_CRC_RETURN_EX)
				return_frame = true;
		}
		framesize = 0;
#if SYNCLINK_GENERIC_HDLC
		{
			info->netdev->stats.rx_errors++;
			info->netdev->stats.rx_frame_errors++;
		}
#endif
	} else
		return_frame = true;

	if (return_frame)
		framesize = buf->count;

	if (debug_level >= DEBUG_LEVEL_BH)
		printk("%s(%d):rx_get_frame(%s) status=%04X size=%d\n",
			__FILE__, __LINE__, info->device_name, status, framesize);

	if (debug_level >= DEBUG_LEVEL_DATA)
		trace_block(info, buf->data, framesize, 0);

	if (framesize) {
		if ((info->params.crc_type & HDLC_CRC_RETURN_EX &&
		      framesize+1 > info->max_frame_size) ||
		    framesize > info->max_frame_size)
			info->icount.rxlong++;
		else {
			if (status & BIT5)
				info->icount.rxok++;

			if (info->params.crc_type & HDLC_CRC_RETURN_EX) {
				*(buf->data + framesize) = status & BIT5 ? RX_OK:RX_CRC_ERROR;
				++framesize;
			}

#if SYNCLINK_GENERIC_HDLC
			if (info->netcount)
				hdlcdev_rx(info, buf->data, framesize);
			else
#endif
				ldisc_receive_buf(tty, buf->data, info->flag_buf, framesize);
		}
	}

	spin_lock_irqsave(&info->lock, flags);
	buf->status = buf->count = 0;
	info->rx_frame_count--;
	info->rx_get++;
	if (info->rx_get >= info->rx_buf_count)
		info->rx_get = 0;
	spin_unlock_irqrestore(&info->lock, flags);

	return true;
}