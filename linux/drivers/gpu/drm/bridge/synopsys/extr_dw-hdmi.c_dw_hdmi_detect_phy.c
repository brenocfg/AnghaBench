#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {scalar_t__ name; void* data; int /*<<< orphan*/ * ops; } ;
struct dw_hdmi {int /*<<< orphan*/  dev; TYPE_2__ phy; TYPE_1__* plat_data; } ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ name; int /*<<< orphan*/  configure; } ;
struct TYPE_5__ {scalar_t__ phy_name; int /*<<< orphan*/  configure_phy; void* phy_data; int /*<<< orphan*/ * phy_ops; scalar_t__ phy_force_vendor; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ DW_HDMI_PHY_VENDOR_PHY ; 
 int ENODEV ; 
 int /*<<< orphan*/  HDMI_CONFIG2_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* dw_hdmi_phys ; 
 int /*<<< orphan*/  dw_hdmi_synopsys_phy_ops ; 
 scalar_t__ hdmi_readb (struct dw_hdmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_hdmi_detect_phy(struct dw_hdmi *hdmi)
{
	unsigned int i;
	u8 phy_type;

	phy_type = hdmi->plat_data->phy_force_vendor ?
				DW_HDMI_PHY_VENDOR_PHY :
				hdmi_readb(hdmi, HDMI_CONFIG2_ID);

	if (phy_type == DW_HDMI_PHY_VENDOR_PHY) {
		/* Vendor PHYs require support from the glue layer. */
		if (!hdmi->plat_data->phy_ops || !hdmi->plat_data->phy_name) {
			dev_err(hdmi->dev,
				"Vendor HDMI PHY not supported by glue layer\n");
			return -ENODEV;
		}

		hdmi->phy.ops = hdmi->plat_data->phy_ops;
		hdmi->phy.data = hdmi->plat_data->phy_data;
		hdmi->phy.name = hdmi->plat_data->phy_name;
		return 0;
	}

	/* Synopsys PHYs are handled internally. */
	for (i = 0; i < ARRAY_SIZE(dw_hdmi_phys); ++i) {
		if (dw_hdmi_phys[i].type == phy_type) {
			hdmi->phy.ops = &dw_hdmi_synopsys_phy_ops;
			hdmi->phy.name = dw_hdmi_phys[i].name;
			hdmi->phy.data = (void *)&dw_hdmi_phys[i];

			if (!dw_hdmi_phys[i].configure &&
			    !hdmi->plat_data->configure_phy) {
				dev_err(hdmi->dev, "%s requires platform support\n",
					hdmi->phy.name);
				return -ENODEV;
			}

			return 0;
		}
	}

	dev_err(hdmi->dev, "Unsupported HDMI PHY type (%02x)\n", phy_type);
	return -ENODEV;
}