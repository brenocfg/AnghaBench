#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned short base; } ;
typedef  TYPE_1__ ppa_struct ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_NORMAL ; 
 int EIO ; 
 int device_check (TYPE_1__*) ; 
 int /*<<< orphan*/  ppa_connect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppa_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  ppa_reset_pulse (unsigned short) ; 
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 

__attribute__((used)) static int ppa_init(ppa_struct *dev)
{
	int retv;
	unsigned short ppb = dev->base;

	ppa_disconnect(dev);
	ppa_connect(dev, CONNECT_NORMAL);

	retv = 2;		/* Failed */

	w_ctr(ppb, 0xe);
	if ((r_str(ppb) & 0x08) == 0x08)
		retv--;

	w_ctr(ppb, 0xc);
	if ((r_str(ppb) & 0x08) == 0x00)
		retv--;

	if (!retv)
		ppa_reset_pulse(ppb);
	udelay(1000);		/* Allow devices to settle down */
	ppa_disconnect(dev);
	udelay(1000);		/* Another delay to allow devices to settle */

	if (retv)
		return -EIO;

	return device_check(dev);
}