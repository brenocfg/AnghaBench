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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_field16 {int dummy; } ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_BUSY_DELAY ; 
 unsigned int REGISTER_USB_BUSY_COUNT ; 
 int /*<<< orphan*/  rt2500usb_register_read_lock (struct rt2x00_dev*,unsigned int const) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field16 (int /*<<< orphan*/ ,struct rt2x00_field16) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2500usb_regbusy_read(struct rt2x00_dev *rt2x00dev,
				  const unsigned int offset,
				  struct rt2x00_field16 field,
				  u16 *reg)
{
	unsigned int i;

	for (i = 0; i < REGISTER_USB_BUSY_COUNT; i++) {
		*reg = rt2500usb_register_read_lock(rt2x00dev, offset);
		if (!rt2x00_get_field16(*reg, field))
			return 1;
		udelay(REGISTER_BUSY_DELAY);
	}

	rt2x00_err(rt2x00dev, "Indirect register access failed: offset=0x%.08x, value=0x%.08x\n",
		   offset, *reg);
	*reg = ~0;

	return 0;
}