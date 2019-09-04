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
typedef  int u32 ;
struct cmac {int /*<<< orphan*/  adapter; TYPE_1__* instance; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int /*<<< orphan*/  REG_DBG (int) ; 
 int /*<<< orphan*/  REG_DEV_SETUP (int) ; 
 int /*<<< orphan*/  REG_MODE_CFG (int) ; 
 int /*<<< orphan*/  REG_PAUSE_CFG (int) ; 
 int /*<<< orphan*/  REG_TX_IFG (int) ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac_set_speed_duplex_fc(struct cmac *mac, int speed, int duplex,
				   int fc)
{
	u32 v;
	int enable, port = mac->instance->index;

	if (speed >= 0 && speed != SPEED_10 && speed != SPEED_100 &&
	    speed != SPEED_1000)
		return -1;
	if (duplex > 0 && duplex != DUPLEX_FULL)
		return -1;

	if (speed >= 0) {
		vsc_read(mac->adapter, REG_MODE_CFG(port), &v);
		enable = v & 3;             /* save tx/rx enables */
		v &= ~0xf;
		v |= 4;                     /* full duplex */
		if (speed == SPEED_1000)
			v |= 8;             /* GigE */
		enable |= v;
		vsc_write(mac->adapter, REG_MODE_CFG(port), v);

		if (speed == SPEED_1000)
			v = 0x82;
		else if (speed == SPEED_100)
			v = 0x84;
		else	/* SPEED_10 */
			v = 0x86;
		vsc_write(mac->adapter, REG_DEV_SETUP(port), v | 1); /* reset */
		vsc_write(mac->adapter, REG_DEV_SETUP(port), v);
		vsc_read(mac->adapter, REG_DBG(port), &v);
		v &= ~0xff00;
		if (speed == SPEED_1000)
			v |= 0x400;
		else if (speed == SPEED_100)
			v |= 0x2000;
		else	/* SPEED_10 */
			v |= 0xff00;
		vsc_write(mac->adapter, REG_DBG(port), v);

		vsc_write(mac->adapter, REG_TX_IFG(port),
			  speed == SPEED_1000 ? 5 : 0x11);
		if (duplex == DUPLEX_HALF)
			enable = 0x0;	/* 100 or 10 */
		else if (speed == SPEED_1000)
			enable = 0xc;
		else	/* SPEED_100 or 10 */
			enable = 0x4;
		enable |= 0x9 << 10;	/* IFG1 */
		enable |= 0x6 << 6;	/* IFG2 */
		enable |= 0x1 << 4;	/* VLAN */
		enable |= 0x3;		/* RX/TX EN */
		vsc_write(mac->adapter, REG_MODE_CFG(port), enable);

	}

	vsc_read(mac->adapter, REG_PAUSE_CFG(port), &v);
	v &= 0xfff0ffff;
	v |= 0x20000;      /* xon/xoff */
	if (fc & PAUSE_RX)
		v |= 0x40000;
	if (fc & PAUSE_TX)
		v |= 0x80000;
	if (fc == (PAUSE_RX | PAUSE_TX))
		v |= 0x10000;
	vsc_write(mac->adapter, REG_PAUSE_CFG(port), v);
	return 0;
}