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
struct ata_device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETFEATURE_SENSE_DATA ; 
 int /*<<< orphan*/  ata_dev_dbg (struct ata_device*,char*,unsigned int) ; 
 unsigned int ata_dev_set_feature (struct ata_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ata_id_has_sense_reporting (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_sense_reporting_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ata_dev_config_sense_reporting(struct ata_device *dev)
{
	unsigned int err_mask;

	if (!ata_id_has_sense_reporting(dev->id))
		return;

	if (ata_id_sense_reporting_enabled(dev->id))
		return;

	err_mask = ata_dev_set_feature(dev, SETFEATURE_SENSE_DATA, 0x1);
	if (err_mask) {
		ata_dev_dbg(dev,
			    "failed to enable Sense Data Reporting, Emask 0x%x\n",
			    err_mask);
	}
}