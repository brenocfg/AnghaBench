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
typedef  enum cc_hw_crypto_key { ____Placeholder_cc_hw_crypto_key } cc_hw_crypto_key ;

/* Variables and functions */
 int END_OF_KEYS ; 
 int KFDE0_KEY ; 
 int KFDE1_KEY ; 
 int KFDE2_KEY ; 
 int KFDE3_KEY ; 

__attribute__((used)) static enum cc_hw_crypto_key cc_slot_to_hw_key(int slot_num)
{
	switch (slot_num) {
	case 0:
		return KFDE0_KEY;
	case 1:
		return KFDE1_KEY;
	case 2:
		return KFDE2_KEY;
	case 3:
		return KFDE3_KEY;
	}
	return END_OF_KEYS;
}