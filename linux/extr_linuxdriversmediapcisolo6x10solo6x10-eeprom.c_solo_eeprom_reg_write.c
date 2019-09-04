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
typedef  int /*<<< orphan*/  u32 ;
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_EEPROM_CTRL ; 
 int /*<<< orphan*/  eeprom_delay () ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_eeprom_reg_write(struct solo_dev *solo_dev, u32 data)
{
	solo_reg_write(solo_dev, SOLO_EEPROM_CTRL, data);
	eeprom_delay();
}