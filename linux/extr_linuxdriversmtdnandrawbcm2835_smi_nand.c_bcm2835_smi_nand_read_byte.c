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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct bcm2835_smi_nand_host {struct bcm2835_smi_instance* smi_inst; } ;
struct bcm2835_smi_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_smi_read_buf (struct bcm2835_smi_instance*,int /*<<< orphan*/ *,int) ; 
 struct bcm2835_smi_nand_host* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t bcm2835_smi_nand_read_byte(struct mtd_info *mtd)
{
	uint8_t byte;
	struct bcm2835_smi_nand_host *host = dev_get_drvdata(mtd->dev.parent);
	struct bcm2835_smi_instance *inst = host->smi_inst;

	bcm2835_smi_read_buf(inst, &byte, 1);
	return byte;
}