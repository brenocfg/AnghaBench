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
typedef  int u8 ;
struct spi_device {int dummy; } ;
struct can_frame {int can_id; int can_dlc; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int HI3110_CAN_MAX_DATA_LEN ; 
 int HI3110_EFF_FLAGS ; 
 int HI3110_FIFO_EXT_DATA_OFF ; 
 size_t HI3110_FIFO_EXT_DLC_OFF ; 
 size_t HI3110_FIFO_ID_OFF ; 
 int HI3110_FIFO_STD_DATA_OFF ; 
 size_t HI3110_FIFO_STD_DLC_OFF ; 
 size_t HI3110_FIFO_TAG_OFF ; 
 int HI3110_TX_EXT_BUF_LEN ; 
 int HI3110_TX_STD_BUF_LEN ; 
 int /*<<< orphan*/  hi3110_hw_tx_frame (struct spi_device*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hi3110_hw_tx(struct spi_device *spi, struct can_frame *frame)
{
	u8 buf[HI3110_TX_EXT_BUF_LEN];

	buf[HI3110_FIFO_TAG_OFF] = 0;

	if (frame->can_id & CAN_EFF_FLAG) {
		/* Extended frame */
		buf[HI3110_FIFO_ID_OFF] = (frame->can_id & CAN_EFF_MASK) >> 21;
		buf[HI3110_FIFO_ID_OFF + 1] =
			(((frame->can_id & CAN_EFF_MASK) >> 13) & 0xe0) |
			HI3110_EFF_FLAGS |
			(((frame->can_id & CAN_EFF_MASK) >> 15) & 0x07);
		buf[HI3110_FIFO_ID_OFF + 2] =
			(frame->can_id & CAN_EFF_MASK) >> 7;
		buf[HI3110_FIFO_ID_OFF + 3] =
			((frame->can_id & CAN_EFF_MASK) << 1) |
			((frame->can_id & CAN_RTR_FLAG) ? 1 : 0);

		buf[HI3110_FIFO_EXT_DLC_OFF] = frame->can_dlc;

		memcpy(buf + HI3110_FIFO_EXT_DATA_OFF,
		       frame->data, frame->can_dlc);

		hi3110_hw_tx_frame(spi, buf, HI3110_TX_EXT_BUF_LEN -
				   (HI3110_CAN_MAX_DATA_LEN - frame->can_dlc));
	} else {
		/* Standard frame */
		buf[HI3110_FIFO_ID_OFF] =   (frame->can_id & CAN_SFF_MASK) >> 3;
		buf[HI3110_FIFO_ID_OFF + 1] =
			((frame->can_id & CAN_SFF_MASK) << 5) |
			((frame->can_id & CAN_RTR_FLAG) ? (1 << 4) : 0);

		buf[HI3110_FIFO_STD_DLC_OFF] = frame->can_dlc;

		memcpy(buf + HI3110_FIFO_STD_DATA_OFF,
		       frame->data, frame->can_dlc);

		hi3110_hw_tx_frame(spi, buf, HI3110_TX_STD_BUF_LEN -
				   (HI3110_CAN_MAX_DATA_LEN - frame->can_dlc));
	}
}