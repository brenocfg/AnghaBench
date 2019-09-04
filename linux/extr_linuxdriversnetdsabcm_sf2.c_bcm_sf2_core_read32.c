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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bcm_sf2_priv {int dummy; } ;
struct b53_device {struct bcm_sf2_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SF2_PAGE_REG_MKADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sf2_core_read32(struct b53_device *dev, u8 page, u8 reg,
			       u32 *val)
{
	struct bcm_sf2_priv *priv = dev->priv;

	*val = core_readl(priv, SF2_PAGE_REG_MKADDR(page, reg));

	return 0;
}