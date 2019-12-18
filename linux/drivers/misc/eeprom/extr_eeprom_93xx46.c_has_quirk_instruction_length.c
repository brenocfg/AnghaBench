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
struct eeprom_93xx46_dev {TYPE_1__* pdata; } ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int EEPROM_93XX46_QUIRK_INSTRUCTION_LENGTH ; 

__attribute__((used)) static inline bool has_quirk_instruction_length(struct eeprom_93xx46_dev *edev)
{
	return edev->pdata->quirks & EEPROM_93XX46_QUIRK_INSTRUCTION_LENGTH;
}