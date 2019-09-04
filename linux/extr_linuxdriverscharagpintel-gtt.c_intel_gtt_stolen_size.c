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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int u16 ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_4__ {TYPE_1__* bridge_dev; scalar_t__ registers; } ;
struct TYPE_3__ {scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  G33_GMCH_GMS_STOLEN_128M 144 
#define  G33_GMCH_GMS_STOLEN_256M 143 
 int /*<<< orphan*/  I830_GMCH_CTRL ; 
#define  I830_GMCH_GMS_LOCAL 142 
 int I830_GMCH_GMS_MASK ; 
#define  I830_GMCH_GMS_STOLEN_1024 141 
#define  I830_GMCH_GMS_STOLEN_512 140 
#define  I830_GMCH_GMS_STOLEN_8192 139 
 scalar_t__ I830_RDRAM_CHANNEL_TYPE ; 
 size_t I830_RDRAM_DDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I830_RDRAM_ND (int /*<<< orphan*/ ) ; 
 int I855_GMCH_GMS_MASK ; 
#define  I855_GMCH_GMS_STOLEN_16M 138 
#define  I855_GMCH_GMS_STOLEN_1M 137 
#define  I855_GMCH_GMS_STOLEN_32M 136 
#define  I855_GMCH_GMS_STOLEN_4M 135 
#define  I855_GMCH_GMS_STOLEN_8M 134 
#define  I915_GMCH_GMS_STOLEN_48M 133 
#define  I915_GMCH_GMS_STOLEN_64M 132 
#define  INTEL_GMCH_GMS_STOLEN_160M 131 
#define  INTEL_GMCH_GMS_STOLEN_224M 130 
#define  INTEL_GMCH_GMS_STOLEN_352M 129 
#define  INTEL_GMCH_GMS_STOLEN_96M 128 
 int INTEL_GTT_GEN ; 
 scalar_t__ KB (int) ; 
 scalar_t__ MB (int const) ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_82830_HB ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_82845G_HB ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__ intel_private ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static resource_size_t intel_gtt_stolen_size(void)
{
	u16 gmch_ctrl;
	u8 rdct;
	int local = 0;
	static const int ddt[4] = { 0, 16, 32, 64 };
	resource_size_t stolen_size = 0;

	if (INTEL_GTT_GEN == 1)
		return 0; /* no stolen mem on i81x */

	pci_read_config_word(intel_private.bridge_dev,
			     I830_GMCH_CTRL, &gmch_ctrl);

	if (intel_private.bridge_dev->device == PCI_DEVICE_ID_INTEL_82830_HB ||
	    intel_private.bridge_dev->device == PCI_DEVICE_ID_INTEL_82845G_HB) {
		switch (gmch_ctrl & I830_GMCH_GMS_MASK) {
		case I830_GMCH_GMS_STOLEN_512:
			stolen_size = KB(512);
			break;
		case I830_GMCH_GMS_STOLEN_1024:
			stolen_size = MB(1);
			break;
		case I830_GMCH_GMS_STOLEN_8192:
			stolen_size = MB(8);
			break;
		case I830_GMCH_GMS_LOCAL:
			rdct = readb(intel_private.registers+I830_RDRAM_CHANNEL_TYPE);
			stolen_size = (I830_RDRAM_ND(rdct) + 1) *
					MB(ddt[I830_RDRAM_DDT(rdct)]);
			local = 1;
			break;
		default:
			stolen_size = 0;
			break;
		}
	} else {
		switch (gmch_ctrl & I855_GMCH_GMS_MASK) {
		case I855_GMCH_GMS_STOLEN_1M:
			stolen_size = MB(1);
			break;
		case I855_GMCH_GMS_STOLEN_4M:
			stolen_size = MB(4);
			break;
		case I855_GMCH_GMS_STOLEN_8M:
			stolen_size = MB(8);
			break;
		case I855_GMCH_GMS_STOLEN_16M:
			stolen_size = MB(16);
			break;
		case I855_GMCH_GMS_STOLEN_32M:
			stolen_size = MB(32);
			break;
		case I915_GMCH_GMS_STOLEN_48M:
			stolen_size = MB(48);
			break;
		case I915_GMCH_GMS_STOLEN_64M:
			stolen_size = MB(64);
			break;
		case G33_GMCH_GMS_STOLEN_128M:
			stolen_size = MB(128);
			break;
		case G33_GMCH_GMS_STOLEN_256M:
			stolen_size = MB(256);
			break;
		case INTEL_GMCH_GMS_STOLEN_96M:
			stolen_size = MB(96);
			break;
		case INTEL_GMCH_GMS_STOLEN_160M:
			stolen_size = MB(160);
			break;
		case INTEL_GMCH_GMS_STOLEN_224M:
			stolen_size = MB(224);
			break;
		case INTEL_GMCH_GMS_STOLEN_352M:
			stolen_size = MB(352);
			break;
		default:
			stolen_size = 0;
			break;
		}
	}

	if (stolen_size > 0) {
		dev_info(&intel_private.bridge_dev->dev, "detected %lluK %s memory\n",
		       (u64)stolen_size / KB(1), local ? "local" : "stolen");
	} else {
		dev_info(&intel_private.bridge_dev->dev,
		       "no pre-allocated video memory detected\n");
		stolen_size = 0;
	}

	return stolen_size;
}