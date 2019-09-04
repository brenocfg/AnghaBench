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
 int VSC73XX_CMD_BLOCK_MASK ; 
 int VSC73XX_CMD_BLOCK_SHIFT ; 
 int VSC73XX_CMD_MODE_SHIFT ; 
 int VSC73XX_CMD_SUBBLOCK_MASK ; 

__attribute__((used)) static u8 vsc73xx_make_addr(u8 mode, u8 block, u8 subblock)
{
	u8 ret;

	ret = (block & VSC73XX_CMD_BLOCK_MASK) << VSC73XX_CMD_BLOCK_SHIFT;
	ret |= (mode & 1) << VSC73XX_CMD_MODE_SHIFT;
	ret |= subblock & VSC73XX_CMD_SUBBLOCK_MASK;

	return ret;
}