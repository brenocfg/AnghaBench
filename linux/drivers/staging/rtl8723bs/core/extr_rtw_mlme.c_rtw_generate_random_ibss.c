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

/* Variables and functions */
 unsigned long jiffies ; 

void rtw_generate_random_ibss(u8 *pibss)
{
	unsigned long curtime = jiffies;

	pibss[0] = 0x02;  /* in ad-hoc mode bit1 must set to 1 */
	pibss[1] = 0x11;
	pibss[2] = 0x87;
	pibss[3] = (u8)(curtime & 0xff) ;/* p[0]; */
	pibss[4] = (u8)((curtime>>8) & 0xff) ;/* p[1]; */
	pibss[5] = (u8)((curtime>>16) & 0xff) ;/* p[2]; */
	return;
}