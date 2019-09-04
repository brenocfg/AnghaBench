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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */
 int DT_IN ; 
 int getfrom_srom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srom_latch (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
srom_address(u_int command, u_long addr, u_char offset)
{
    int i, a;

    a = offset << 2;
    for (i=0; i<6; i++, a <<= 1) {
	srom_latch(command | ((a & 0x80) ? DT_IN : 0), addr);
    }
    udelay(1);

    i = (getfrom_srom(addr) >> 3) & 0x01;
}