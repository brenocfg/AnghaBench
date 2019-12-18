#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sf_size; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int FLASH_CFG_START ; 
 unsigned int FLASH_FPGA_CFG_START ; 

unsigned int t4_flash_cfg_addr(struct adapter *adapter)
{
	if (adapter->params.sf_size == 0x100000)
		return FLASH_FPGA_CFG_START;
	else
		return FLASH_CFG_START;
}