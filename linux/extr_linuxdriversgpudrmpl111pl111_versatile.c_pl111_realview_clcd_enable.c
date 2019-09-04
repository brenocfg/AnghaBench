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
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CLCD ; 
 int /*<<< orphan*/  SYS_CLCD_CONNECTOR_MASK ; 
 int SYS_CLCD_NLCDIOON ; 
 int SYS_CLCD_PWR3V5SWITCH ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  versatile_syscon_map ; 

__attribute__((used)) static void pl111_realview_clcd_enable(struct drm_device *drm, u32 format)
{
	dev_info(drm->dev, "enable RealView CLCD connectors\n");
	regmap_update_bits(versatile_syscon_map,
			   SYS_CLCD,
			   SYS_CLCD_CONNECTOR_MASK,
			   SYS_CLCD_NLCDIOON | SYS_CLCD_PWR3V5SWITCH);
}