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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 int FLASH_VOUT_MIN ; 
 scalar_t__ FLASH_VOUT_RMIN ; 
 int FLASH_VOUT_STEP ; 

__attribute__((used)) static inline u8 max77693_led_vout_to_reg(u32 mv)
{
	return (mv - FLASH_VOUT_MIN) / FLASH_VOUT_STEP + FLASH_VOUT_RMIN;
}