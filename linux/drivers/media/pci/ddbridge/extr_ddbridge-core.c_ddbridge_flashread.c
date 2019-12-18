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
typedef  int u32 ;
struct ddb {int dummy; } ;

/* Variables and functions */
 int flashio (struct ddb*,int,int*,int,int*,int) ; 

int ddbridge_flashread(struct ddb *dev, u32 link, u8 *buf, u32 addr, u32 len)
{
	u8 cmd[4] = {0x03, (addr >> 16) & 0xff,
		     (addr >> 8) & 0xff, addr & 0xff};

	return flashio(dev, link, cmd, 4, buf, len);
}