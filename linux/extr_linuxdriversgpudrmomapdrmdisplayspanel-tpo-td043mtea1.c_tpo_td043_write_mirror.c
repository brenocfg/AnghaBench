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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int TPO_R04_CP_CLK_FREQ_1H ; 
 int TPO_R04_NFLIP_H ; 
 int TPO_R04_NFLIP_V ; 
 int TPO_R04_VGL_FREQ_1H ; 
 int tpo_td043_write (struct spi_device*,int,int) ; 

__attribute__((used)) static int tpo_td043_write_mirror(struct spi_device *spi, bool h, bool v)
{
	u8 reg4 = TPO_R04_NFLIP_H | TPO_R04_NFLIP_V |
		TPO_R04_CP_CLK_FREQ_1H | TPO_R04_VGL_FREQ_1H;
	if (h)
		reg4 &= ~TPO_R04_NFLIP_H;
	if (v)
		reg4 &= ~TPO_R04_NFLIP_V;

	return tpo_td043_write(spi, 4, reg4);
}