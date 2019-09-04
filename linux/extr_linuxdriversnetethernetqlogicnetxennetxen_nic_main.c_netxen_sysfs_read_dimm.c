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
typedef  int u8 ;
typedef  int u32 ;
struct netxen_dimm_cfg {int presence; int dimm_type; int size; int /*<<< orphan*/  mem_type; } ;
struct netxen_adapter {struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {size_t size; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NETXEN_DIMM_CAPABILITY ; 
 int NETXEN_DIMM_DATAWIDTH (int) ; 
 int /*<<< orphan*/  NETXEN_DIMM_MEMTYPE (int) ; 
 int NETXEN_DIMM_MEMTYPE_DDR2_SDRAM ; 
 int /*<<< orphan*/  NETXEN_DIMM_MEM_DDR2_SDRAM ; 
 int NETXEN_DIMM_NUMBANKS (int) ; 
 int NETXEN_DIMM_NUMCOLS (int) ; 
 int NETXEN_DIMM_NUMRANKS (int) ; 
 int NETXEN_DIMM_NUMROWS (int) ; 
 int NETXEN_DIMM_PRESENT ; 
 int NETXEN_DIMM_SIZE ; 
 int NETXEN_DIMM_STD_MEM_SIZE ; 
 int NETXEN_DIMM_TYPE (int) ; 
#define  NETXEN_DIMM_TYPE_Micro_DIMM 133 
#define  NETXEN_DIMM_TYPE_Mini_RDIMM 132 
#define  NETXEN_DIMM_TYPE_Mini_UDIMM 131 
#define  NETXEN_DIMM_TYPE_RDIMM 130 
#define  NETXEN_DIMM_TYPE_SO_DIMM 129 
#define  NETXEN_DIMM_TYPE_UDIMM 128 
 int NETXEN_DIMM_VALID_FLAG ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 struct netxen_adapter* dev_get_drvdata (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (char*,struct netxen_dimm_cfg*,int) ; 
 int /*<<< orphan*/  memset (struct netxen_dimm_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 

__attribute__((used)) static ssize_t
netxen_sysfs_read_dimm(struct file *filp, struct kobject *kobj,
		struct bin_attribute *attr,
		char *buf, loff_t offset, size_t size)
{
	struct device *dev = kobj_to_dev(kobj);
	struct netxen_adapter *adapter = dev_get_drvdata(dev);
	struct net_device *netdev = adapter->netdev;
	struct netxen_dimm_cfg dimm;
	u8 dw, rows, cols, banks, ranks;
	u32 val;

	if (size < attr->size) {
		netdev_err(netdev, "Invalid size\n");
		return -EINVAL;
	}

	memset(&dimm, 0, sizeof(struct netxen_dimm_cfg));
	val = NXRD32(adapter, NETXEN_DIMM_CAPABILITY);

	/* Checks if DIMM info is valid. */
	if (val & NETXEN_DIMM_VALID_FLAG) {
		netdev_err(netdev, "Invalid DIMM flag\n");
		dimm.presence = 0xff;
		goto out;
	}

	rows = NETXEN_DIMM_NUMROWS(val);
	cols = NETXEN_DIMM_NUMCOLS(val);
	ranks = NETXEN_DIMM_NUMRANKS(val);
	banks = NETXEN_DIMM_NUMBANKS(val);
	dw = NETXEN_DIMM_DATAWIDTH(val);

	dimm.presence = (val & NETXEN_DIMM_PRESENT);

	/* Checks if DIMM info is present. */
	if (!dimm.presence) {
		netdev_err(netdev, "DIMM not present\n");
		goto out;
	}

	dimm.dimm_type = NETXEN_DIMM_TYPE(val);

	switch (dimm.dimm_type) {
	case NETXEN_DIMM_TYPE_RDIMM:
	case NETXEN_DIMM_TYPE_UDIMM:
	case NETXEN_DIMM_TYPE_SO_DIMM:
	case NETXEN_DIMM_TYPE_Micro_DIMM:
	case NETXEN_DIMM_TYPE_Mini_RDIMM:
	case NETXEN_DIMM_TYPE_Mini_UDIMM:
		break;
	default:
		netdev_err(netdev, "Invalid DIMM type %x\n", dimm.dimm_type);
		goto out;
	}

	if (val & NETXEN_DIMM_MEMTYPE_DDR2_SDRAM)
		dimm.mem_type = NETXEN_DIMM_MEM_DDR2_SDRAM;
	else
		dimm.mem_type = NETXEN_DIMM_MEMTYPE(val);

	if (val & NETXEN_DIMM_SIZE) {
		dimm.size = NETXEN_DIMM_STD_MEM_SIZE;
		goto out;
	}

	if (!rows) {
		netdev_err(netdev, "Invalid no of rows %x\n", rows);
		goto out;
	}

	if (!cols) {
		netdev_err(netdev, "Invalid no of columns %x\n", cols);
		goto out;
	}

	if (!banks) {
		netdev_err(netdev, "Invalid no of banks %x\n", banks);
		goto out;
	}

	ranks += 1;

	switch (dw) {
	case 0x0:
		dw = 32;
		break;
	case 0x1:
		dw = 33;
		break;
	case 0x2:
		dw = 36;
		break;
	case 0x3:
		dw = 64;
		break;
	case 0x4:
		dw = 72;
		break;
	case 0x5:
		dw = 80;
		break;
	case 0x6:
		dw = 128;
		break;
	case 0x7:
		dw = 144;
		break;
	default:
		netdev_err(netdev, "Invalid data-width %x\n", dw);
		goto out;
	}

	dimm.size = ((1 << rows) * (1 << cols) * dw * banks * ranks) / 8;
	/* Size returned in MB. */
	dimm.size = (dimm.size) / 0x100000;
out:
	memcpy(buf, &dimm, sizeof(struct netxen_dimm_cfg));
	return sizeof(struct netxen_dimm_cfg);

}