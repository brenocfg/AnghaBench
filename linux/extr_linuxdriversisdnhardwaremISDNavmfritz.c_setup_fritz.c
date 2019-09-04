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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct fritzcard {int type; scalar_t__ addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; TYPE_1__ isac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
#define  AVM_FRITZ_PCI 129 
#define  AVM_FRITZ_PCIV2 128 
 int /*<<< orphan*/  AVM_HDLC_1 ; 
 scalar_t__ AVM_HDLC_STATUS_1 ; 
 scalar_t__ CHIP_INDEX ; 
 scalar_t__ CHIP_WINDOW ; 
 int DEBUG_HW ; 
 int EIO ; 
 int ENODEV ; 
 scalar_t__ HDLC_STATUS ; 
 int /*<<< orphan*/  IPAC_TYPE_ISAC ; 
 int /*<<< orphan*/  IPAC_TYPE_ISACX ; 
 int /*<<< orphan*/  ISAC ; 
 int /*<<< orphan*/  V1 ; 
 int /*<<< orphan*/  V2 ; 
 int debug ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setup_fritz(struct fritzcard *fc)
{
	u32 val, ver;

	if (!request_region(fc->addr, 32, fc->name)) {
		pr_info("%s: AVM config port %x-%x already in use\n",
			fc->name, fc->addr, fc->addr + 31);
		return -EIO;
	}
	switch (fc->type) {
	case AVM_FRITZ_PCI:
		val = inl(fc->addr);
		outl(AVM_HDLC_1, fc->addr + CHIP_INDEX);
		ver = inl(fc->addr + CHIP_WINDOW + HDLC_STATUS) >> 24;
		if (debug & DEBUG_HW) {
			pr_notice("%s: PCI stat %#x\n", fc->name, val);
			pr_notice("%s: PCI Class %X Rev %d\n", fc->name,
				  val & 0xff, (val >> 8) & 0xff);
			pr_notice("%s: HDLC version %x\n", fc->name, ver & 0xf);
		}
		ASSIGN_FUNC(V1, ISAC, fc->isac);
		fc->isac.type = IPAC_TYPE_ISAC;
		break;
	case AVM_FRITZ_PCIV2:
		val = inl(fc->addr);
		ver = inl(fc->addr + AVM_HDLC_STATUS_1) >> 24;
		if (debug & DEBUG_HW) {
			pr_notice("%s: PCI V2 stat %#x\n", fc->name, val);
			pr_notice("%s: PCI V2 Class %X Rev %d\n", fc->name,
				  val & 0xff, (val >> 8) & 0xff);
			pr_notice("%s: HDLC version %x\n", fc->name, ver & 0xf);
		}
		ASSIGN_FUNC(V2, ISAC, fc->isac);
		fc->isac.type = IPAC_TYPE_ISACX;
		break;
	default:
		release_region(fc->addr, 32);
		pr_info("%s: AVM unknown type %d\n", fc->name, fc->type);
		return -ENODEV;
	}
	pr_notice("%s: %s config irq:%d base:0x%X\n", fc->name,
		  (fc->type == AVM_FRITZ_PCI) ? "AVM Fritz!CARD PCI" :
		  "AVM Fritz!CARD PCIv2", fc->irq, fc->addr);
	return 0;
}