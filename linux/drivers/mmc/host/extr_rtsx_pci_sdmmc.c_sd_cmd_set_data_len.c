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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BLOCK_CNT_H ; 
 int /*<<< orphan*/  SD_BLOCK_CNT_L ; 
 int /*<<< orphan*/  SD_BYTE_CNT_H ; 
 int /*<<< orphan*/  SD_BYTE_CNT_L ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void sd_cmd_set_data_len(struct rtsx_pcr *pcr, u16 blocks, u16 blksz)
{
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BLOCK_CNT_L, 0xFF, blocks);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BLOCK_CNT_H, 0xFF, blocks >> 8);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BYTE_CNT_L, 0xFF, blksz);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_BYTE_CNT_H, 0xFF, blksz >> 8);
}