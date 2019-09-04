#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct octeon_device {int rev_id; TYPE_1__* pci_dev; int /*<<< orphan*/  chip_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  card_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIQUIDIO_VERSION ; 
#define  OCTEON_CN23XX_PCIID_PF 130 
 int /*<<< orphan*/  OCTEON_CN23XX_PF_VID ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
#define  OCTEON_CN66XX_PCIID 129 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
#define  OCTEON_CN68XX_PCIID 128 
 int /*<<< orphan*/  OCTEON_MAJOR_REV (struct octeon_device*) ; 
 int /*<<< orphan*/  OCTEON_MINOR_REV (struct octeon_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lio_setup_cn66xx_octeon_device (struct octeon_device*) ; 
 int lio_setup_cn68xx_octeon_device (struct octeon_device*) ; 
 TYPE_2__* octeon_get_conf (struct octeon_device*) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int,int*) ; 
 int setup_cn23xx_octeon_pf_device (struct octeon_device*) ; 

__attribute__((used)) static int octeon_chip_specific_setup(struct octeon_device *oct)
{
	u32 dev_id, rev_id;
	int ret = 1;
	char *s;

	pci_read_config_dword(oct->pci_dev, 0, &dev_id);
	pci_read_config_dword(oct->pci_dev, 8, &rev_id);
	oct->rev_id = rev_id & 0xff;

	switch (dev_id) {
	case OCTEON_CN68XX_PCIID:
		oct->chip_id = OCTEON_CN68XX;
		ret = lio_setup_cn68xx_octeon_device(oct);
		s = "CN68XX";
		break;

	case OCTEON_CN66XX_PCIID:
		oct->chip_id = OCTEON_CN66XX;
		ret = lio_setup_cn66xx_octeon_device(oct);
		s = "CN66XX";
		break;

	case OCTEON_CN23XX_PCIID_PF:
		oct->chip_id = OCTEON_CN23XX_PF_VID;
		ret = setup_cn23xx_octeon_pf_device(oct);
		if (ret)
			break;
#ifdef CONFIG_PCI_IOV
		if (!ret)
			pci_sriov_set_totalvfs(oct->pci_dev,
					       oct->sriov_info.max_vfs);
#endif
		s = "CN23XX";
		break;

	default:
		s = "?";
		dev_err(&oct->pci_dev->dev, "Unknown device found (dev_id: %x)\n",
			dev_id);
	}

	if (!ret)
		dev_info(&oct->pci_dev->dev, "%s PASS%d.%d %s Version: %s\n", s,
			 OCTEON_MAJOR_REV(oct),
			 OCTEON_MINOR_REV(oct),
			 octeon_get_conf(oct)->card_name,
			 LIQUIDIO_VERSION);

	return ret;
}