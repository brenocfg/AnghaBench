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
struct lanai_dev {int /*<<< orphan*/  magicno; scalar_t__ serialno; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_MAGIC_VALUE ; 

__attribute__((used)) static int eeprom_validate(struct lanai_dev *lanai)
{
	lanai->serialno = 0;
	lanai->magicno = EEPROM_MAGIC_VALUE;
	return 0;
}