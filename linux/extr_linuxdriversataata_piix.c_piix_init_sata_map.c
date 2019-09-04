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
typedef  size_t u8 ;
struct piix_map_db {int** map; size_t mask; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ata_port_info {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLAG_SLAVE_POSS ; 
 int /*<<< orphan*/  ICH5_PMR ; 
#define  IDE 130 
#define  NA 129 
#define  RV 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 size_t ich_pata_100 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,size_t*) ; 
 struct ata_port_info* piix_port_info ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,...) ; 

__attribute__((used)) static const int *piix_init_sata_map(struct pci_dev *pdev,
				     struct ata_port_info *pinfo,
				     const struct piix_map_db *map_db)
{
	const int *map;
	int i, invalid_map = 0;
	u8 map_value;
	char buf[32];
	char *p = buf, *end = buf + sizeof(buf);

	pci_read_config_byte(pdev, ICH5_PMR, &map_value);

	map = map_db->map[map_value & map_db->mask];

	for (i = 0; i < 4; i++) {
		switch (map[i]) {
		case RV:
			invalid_map = 1;
			p += scnprintf(p, end - p, " XX");
			break;

		case NA:
			p += scnprintf(p, end - p, " --");
			break;

		case IDE:
			WARN_ON((i & 1) || map[i + 1] != IDE);
			pinfo[i / 2] = piix_port_info[ich_pata_100];
			i++;
			p += scnprintf(p, end - p, " IDE IDE");
			break;

		default:
			p += scnprintf(p, end - p, " P%d", map[i]);
			if (i & 1)
				pinfo[i / 2].flags |= ATA_FLAG_SLAVE_POSS;
			break;
		}
	}
	dev_info(&pdev->dev, "MAP [%s ]\n", buf);

	if (invalid_map)
		dev_err(&pdev->dev, "invalid MAP value %u\n", map_value);

	return map;
}