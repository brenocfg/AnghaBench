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
struct mtk_tphy {int dummy; } ;
struct mtk_phy_instance {scalar_t__ type; int /*<<< orphan*/  eye_term; int /*<<< orphan*/  eye_vrt; int /*<<< orphan*/  eye_src; int /*<<< orphan*/  bc12_en; TYPE_1__* phy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void phy_parse_property(struct mtk_tphy *tphy,
				struct mtk_phy_instance *instance)
{
	struct device *dev = &instance->phy->dev;

	if (instance->type != PHY_TYPE_USB2)
		return;

	instance->bc12_en = device_property_read_bool(dev, "mediatek,bc12");
	device_property_read_u32(dev, "mediatek,eye-src",
				 &instance->eye_src);
	device_property_read_u32(dev, "mediatek,eye-vrt",
				 &instance->eye_vrt);
	device_property_read_u32(dev, "mediatek,eye-term",
				 &instance->eye_term);
	dev_dbg(dev, "bc12:%d, src:%d, vrt:%d, term:%d\n",
		instance->bc12_en, instance->eye_src,
		instance->eye_vrt, instance->eye_term);
}