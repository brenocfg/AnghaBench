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
typedef  int /*<<< orphan*/  uint8_t ;
struct fmc_device {int eeprom_len; int /*<<< orphan*/ * eeprom; int /*<<< orphan*/  dev; int /*<<< orphan*/  slot_id; int /*<<< orphan*/  carrier_name; int /*<<< orphan*/ * hwdev; } ;

/* Variables and functions */
 scalar_t__ LINELEN ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dump_line (int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fmc_must_dump_eeprom ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 

void fmc_dump_eeprom(const struct fmc_device *fmc)
{
	const uint8_t *line, *prev;
	int i;

	if (!fmc_must_dump_eeprom)
		return;

	pr_info("FMC: %s (%s), slot %i, device %s\n", dev_name(fmc->hwdev),
		fmc->carrier_name, fmc->slot_id, dev_name(&fmc->dev));
	pr_info("FMC: dumping eeprom 0x%x (%i) bytes\n", fmc->eeprom_len,
	       fmc->eeprom_len);

	line = fmc->eeprom;
	prev = NULL;
	for (i = 0; i < fmc->eeprom_len; i += LINELEN, line += LINELEN)
		prev = dump_line(i, line, prev);
}