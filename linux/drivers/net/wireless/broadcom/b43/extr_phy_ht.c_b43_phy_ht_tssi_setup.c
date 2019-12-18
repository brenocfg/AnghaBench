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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
#define  R2059_C1 130 
#define  R2059_C2 129 
#define  R2059_C3 128 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int const,int) ; 

__attribute__((used)) static void b43_phy_ht_tssi_setup(struct b43_wldev *dev)
{
	static const u16 routing[] = { R2059_C1, R2059_C2, R2059_C3, };
	int core;

	/* 0x159 is probably TX_SSI_MUX or TSSIG (by comparing to N-PHY) */
	for (core = 0; core < 3; core++) {
		b43_radio_set(dev, 0x8bf, 0x1);
		b43_radio_write(dev, routing[core] | 0x0159, 0x0011);
	}
}