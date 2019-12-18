#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_8__ {int intr_interval; int /*<<< orphan*/  net; TYPE_1__* usb; } ;
typedef  TYPE_2__ pegasus_t ;
struct TYPE_7__ {scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  netif_info (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  read_eprom_word (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  write_eprom_word (TYPE_2__*,int,int) ; 

__attribute__((used)) static inline void get_interrupt_interval(pegasus_t *pegasus)
{
	u16 data;
	u8 interval;

	read_eprom_word(pegasus, 4, &data);
	interval = data >> 8;
	if (pegasus->usb->speed != USB_SPEED_HIGH) {
		if (interval < 0x80) {
			netif_info(pegasus, timer, pegasus->net,
				   "intr interval changed from %ums to %ums\n",
				   interval, 0x80);
			interval = 0x80;
			data = (data & 0x00FF) | ((u16)interval << 8);
#ifdef PEGASUS_WRITE_EEPROM
			write_eprom_word(pegasus, 4, data);
#endif
		}
	}
	pegasus->intr_interval = interval;
}