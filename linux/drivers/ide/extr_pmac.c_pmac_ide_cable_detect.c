#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct device_node {int dummy; } ;
struct TYPE_7__ {struct device_node* node; } ;
typedef  TYPE_2__ pmac_ide_hwif_t ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {TYPE_1__ gendev; } ;
typedef  TYPE_3__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40 ; 
 int /*<<< orphan*/  ATA_CBL_PATA40_SHORT ; 
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 TYPE_2__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static u8 pmac_ide_cable_detect(ide_hwif_t *hwif)
{
	pmac_ide_hwif_t *pmif = dev_get_drvdata(hwif->gendev.parent);
	struct device_node *np = pmif->node;
	const char *cable = of_get_property(np, "cable-type", NULL);
	struct device_node *root = of_find_node_by_path("/");
	const char *model = of_get_property(root, "model", NULL);

	of_node_put(root);
	/* Get cable type from device-tree. */
	if (cable && !strncmp(cable, "80-", 3)) {
		/* Some drives fail to detect 80c cable in PowerBook */
		/* These machine use proprietary short IDE cable anyway */
		if (!strncmp(model, "PowerBook", 9))
			return ATA_CBL_PATA40_SHORT;
		else
			return ATA_CBL_PATA80;
	}

	/*
	 * G5's seem to have incorrect cable type in device-tree.
	 * Let's assume they have a 80 conductor cable, this seem
	 * to be always the case unless the user mucked around.
	 */
	if (of_device_is_compatible(np, "K2-UATA") ||
	    of_device_is_compatible(np, "shasta-ata"))
		return ATA_CBL_PATA80;

	return ATA_CBL_PATA40;
}