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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int REG_SD_BLOCK_CNT_H ; 
 int REG_SD_BLOCK_CNT_L ; 
 scalar_t__ REG_SD_BUS_STAT ; 
 int REG_SD_BYTE_CNT_H ; 
 int REG_SD_BYTE_CNT_L ; 
 int REG_SD_CFG1 ; 
 int REG_SD_CFG2 ; 
 int REG_SD_CFG3 ; 
 int REG_SD_CMD0 ; 
 int REG_SD_CMD1 ; 
 int REG_SD_CMD2 ; 
 int REG_SD_CMD3 ; 
 int REG_SD_CMD4 ; 
 int REG_SD_CMD5 ; 
 scalar_t__ REG_SD_DCMPS0_CTL ; 
 scalar_t__ REG_SD_DCMPS1_CTL ; 
 scalar_t__ REG_SD_PAD_CTL ; 
 scalar_t__ REG_SD_PUSH_POINT_CTL ; 
 scalar_t__ REG_SD_SAMPLE_POINT_CTL ; 
 int REG_SD_STAT1 ; 
 scalar_t__ REG_SD_STAT2 ; 
 int REG_SD_TRANSFER ; 
 scalar_t__ REG_SD_VPCLK0_CTL ; 
 scalar_t__ REG_SD_VPCLK1_CTL ; 

__attribute__((used)) static void sd_init_reg_addr(struct rtsx_chip *chip)
{
	REG_SD_CFG1 = 0xFD31;
	REG_SD_CFG2 = 0xFD33;
	REG_SD_CFG3 = 0xFD3E;
	REG_SD_STAT1 = 0xFD30;
	REG_SD_STAT2 = 0;
	REG_SD_BUS_STAT = 0;
	REG_SD_PAD_CTL = 0;
	REG_SD_SAMPLE_POINT_CTL = 0;
	REG_SD_PUSH_POINT_CTL = 0;
	REG_SD_CMD0 = 0xFD34;
	REG_SD_CMD1 = 0xFD35;
	REG_SD_CMD2 = 0xFD36;
	REG_SD_CMD3 = 0xFD37;
	REG_SD_CMD4 = 0xFD38;
	REG_SD_CMD5 = 0xFD5A;
	REG_SD_BYTE_CNT_L = 0xFD39;
	REG_SD_BYTE_CNT_H = 0xFD3A;
	REG_SD_BLOCK_CNT_L = 0xFD3B;
	REG_SD_BLOCK_CNT_H = 0xFD3C;
	REG_SD_TRANSFER = 0xFD32;
	REG_SD_VPCLK0_CTL = 0;
	REG_SD_VPCLK1_CTL = 0;
	REG_SD_DCMPS0_CTL = 0;
	REG_SD_DCMPS1_CTL = 0;
}