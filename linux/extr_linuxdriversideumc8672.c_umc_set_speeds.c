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
typedef  size_t u8 ;

/* Variables and functions */
 int /*<<< orphan*/  out_umc (int,int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  printk (char*,size_t,size_t,size_t,size_t) ; 
 int** speedtab ; 

__attribute__((used)) static void umc_set_speeds(u8 speeds[])
{
	int i, tmp;

	outb_p(0x5A, 0x108); /* enable umc */

	out_umc(0xd7, (speedtab[0][speeds[2]] | (speedtab[0][speeds[3]]<<4)));
	out_umc(0xd6, (speedtab[0][speeds[0]] | (speedtab[0][speeds[1]]<<4)));
	tmp = 0;
	for (i = 3; i >= 0; i--)
		tmp = (tmp << 2) | speedtab[1][speeds[i]];
	out_umc(0xdc, tmp);
	for (i = 0; i < 4; i++) {
		out_umc(0xd0 + i, speedtab[2][speeds[i]]);
		out_umc(0xd8 + i, speedtab[2][speeds[i]]);
	}
	outb_p(0xa5, 0x108); /* disable umc */

	printk("umc8672: drive speeds [0 to 11]: %d %d %d %d\n",
		speeds[0], speeds[1], speeds[2], speeds[3]);
}