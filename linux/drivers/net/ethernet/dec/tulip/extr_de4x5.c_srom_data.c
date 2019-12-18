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
typedef  int s32 ;

/* Variables and functions */
 int DT_CLK ; 
 int getfrom_srom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendto_srom (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static short
srom_data(u_int command, u_long addr)
{
    int i;
    short word = 0;
    s32 tmp;

    for (i=0; i<16; i++) {
	sendto_srom(command  | DT_CLK, addr);
	tmp = getfrom_srom(addr);
	sendto_srom(command, addr);

	word = (word << 1) | ((tmp >> 3) & 0x01);
    }

    sendto_srom(command & 0x0000ff00, addr);

    return word;
}