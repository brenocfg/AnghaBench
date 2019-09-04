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
struct pci_dev {int revision; int /*<<< orphan*/  dev; } ;
struct agp_bridge_data {int major_version; scalar_t__ minor_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void amd8151_init(struct pci_dev *pdev, struct agp_bridge_data *bridge)
{
	char *revstring;

	switch (pdev->revision) {
	case 0x01: revstring="A0"; break;
	case 0x02: revstring="A1"; break;
	case 0x11: revstring="B0"; break;
	case 0x12: revstring="B1"; break;
	case 0x13: revstring="B2"; break;
	case 0x14: revstring="B3"; break;
	default:   revstring="??"; break;
	}

	dev_info(&pdev->dev, "AMD 8151 AGP Bridge rev %s\n", revstring);

	/*
	 * Work around errata.
	 * Chips before B2 stepping incorrectly reporting v3.5
	 */
	if (pdev->revision < 0x13) {
		dev_info(&pdev->dev, "correcting AGP revision (reports 3.5, is really 3.0)\n");
		bridge->major_version = 3;
		bridge->minor_version = 0;
	}
}