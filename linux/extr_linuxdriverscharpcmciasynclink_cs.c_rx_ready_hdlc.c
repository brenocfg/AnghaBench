#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  buf_overrun; } ;
struct TYPE_10__ {int rx_put; int rx_buf_size; int rx_frame_count; int rx_buf_count; int rx_overflow; scalar_t__ max_frame_size; int /*<<< orphan*/  pending_bh; TYPE_1__ icount; int /*<<< orphan*/  rx_enabled; scalar_t__ rx_buf; } ;
struct TYPE_9__ {unsigned char status; scalar_t__ count; unsigned char* data; } ;
typedef  TYPE_2__ RXBUF ;
typedef  TYPE_3__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BH_RECEIVE ; 
 scalar_t__ CHA ; 
 int /*<<< orphan*/  CMD_RXFIFO ; 
 int /*<<< orphan*/  CMD_RXRESET ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ RBCL ; 
 scalar_t__ RXFIFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  issue_command (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int) ; 
 int read_reg (TYPE_3__*,scalar_t__) ; 
 unsigned short read_reg16 (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void rx_ready_hdlc(MGSLPC_INFO *info, int eom)
{
	unsigned char data[2];
	unsigned char fifo_count, read_count, i;
	RXBUF *buf = (RXBUF*)(info->rx_buf + (info->rx_put * info->rx_buf_size));

	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):rx_ready_hdlc(eom=%d)\n", __FILE__, __LINE__, eom);

	if (!info->rx_enabled)
		return;

	if (info->rx_frame_count >= info->rx_buf_count) {
		/* no more free buffers */
		issue_command(info, CHA, CMD_RXRESET);
		info->pending_bh |= BH_RECEIVE;
		info->rx_overflow = true;
		info->icount.buf_overrun++;
		return;
	}

	if (eom) {
		/* end of frame, get FIFO count from RBCL register */
		fifo_count = (unsigned char)(read_reg(info, CHA+RBCL) & 0x1f);
		if (fifo_count == 0)
			fifo_count = 32;
	} else
		fifo_count = 32;

	do {
		if (fifo_count == 1) {
			read_count = 1;
			data[0] = read_reg(info, CHA + RXFIFO);
		} else {
			read_count = 2;
			*((unsigned short *) data) = read_reg16(info, CHA + RXFIFO);
		}
		fifo_count -= read_count;
		if (!fifo_count && eom)
			buf->status = data[--read_count];

		for (i = 0; i < read_count; i++) {
			if (buf->count >= info->max_frame_size) {
				/* frame too large, reset receiver and reset current buffer */
				issue_command(info, CHA, CMD_RXRESET);
				buf->count = 0;
				return;
			}
			*(buf->data + buf->count) = data[i];
			buf->count++;
		}
	} while (fifo_count);

	if (eom) {
		info->pending_bh |= BH_RECEIVE;
		info->rx_frame_count++;
		info->rx_put++;
		if (info->rx_put >= info->rx_buf_count)
			info->rx_put = 0;
	}
	issue_command(info, CHA, CMD_RXFIFO);
}