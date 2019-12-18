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
struct lan78xx_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_RX ; 
 int MAC_RX_MAX_SIZE_MASK_ ; 
 int MAC_RX_MAX_SIZE_SHIFT_ ; 
 int MAC_RX_RXEN_ ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan78xx_set_rx_max_frame_length(struct lan78xx_net *dev, int size)
{
	int ret = 0;
	u32 buf;
	bool rxenabled;

	ret = lan78xx_read_reg(dev, MAC_RX, &buf);

	rxenabled = ((buf & MAC_RX_RXEN_) != 0);

	if (rxenabled) {
		buf &= ~MAC_RX_RXEN_;
		ret = lan78xx_write_reg(dev, MAC_RX, buf);
	}

	/* add 4 to size for FCS */
	buf &= ~MAC_RX_MAX_SIZE_MASK_;
	buf |= (((size + 4) << MAC_RX_MAX_SIZE_SHIFT_) & MAC_RX_MAX_SIZE_MASK_);

	ret = lan78xx_write_reg(dev, MAC_RX, buf);

	if (rxenabled) {
		buf |= MAC_RX_RXEN_;
		ret = lan78xx_write_reg(dev, MAC_RX, buf);
	}

	return 0;
}