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
typedef  unsigned int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  TP_NVRAM_ADDR_BRIGHTNESS ; 
 unsigned int TP_NVRAM_MASK_LEVEL_BRIGHTNESS ; 
 unsigned int TP_NVRAM_POS_LEVEL_BRIGHTNESS ; 
 unsigned int bright_maxlvl ; 
 unsigned int nvram_read_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int tpacpi_brightness_nvram_get(void)
{
	u8 lnvram;

	lnvram = (nvram_read_byte(TP_NVRAM_ADDR_BRIGHTNESS)
		  & TP_NVRAM_MASK_LEVEL_BRIGHTNESS)
		  >> TP_NVRAM_POS_LEVEL_BRIGHTNESS;
	lnvram &= bright_maxlvl;

	return lnvram;
}