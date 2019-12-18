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
typedef  scalar_t__ u16 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int calculate_word_cnts (int) ; 
 scalar_t__ efuse_available_max_size ; 
 scalar_t__ efuse_one_byte_read (struct _adapter*,scalar_t__,int*) ; 

u16 r8712_efuse_get_current_size(struct _adapter *adapter)
{
	int bContinual = true;
	u16 efuse_addr = 0;
	u8 hworden = 0;
	u8 efuse_data, word_cnts = 0;

	while (bContinual && efuse_one_byte_read(adapter, efuse_addr,
	       &efuse_data) && (efuse_addr < efuse_available_max_size)) {
		if (efuse_data != 0xFF) {
			hworden =  efuse_data & 0x0F;
			word_cnts = calculate_word_cnts(hworden);
			/* read next header */
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
		} else {
			bContinual = false;
		}
	}
	return efuse_addr;
}