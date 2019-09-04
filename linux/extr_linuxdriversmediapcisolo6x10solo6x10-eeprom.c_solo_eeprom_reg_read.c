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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 unsigned int EE_DATA_READ ; 
 int /*<<< orphan*/  SOLO_EEPROM_CTRL ; 
 unsigned int solo_reg_read (struct solo_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int solo_eeprom_reg_read(struct solo_dev *solo_dev)
{
	return solo_reg_read(solo_dev, SOLO_EEPROM_CTRL) & EE_DATA_READ;
}