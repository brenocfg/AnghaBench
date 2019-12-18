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
struct mtk_sgmii {int /*<<< orphan*/ * regmap; } ;
struct mtk_eth {TYPE_1__* soc; struct mtk_sgmii* sgmii; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_SHARED_SGMII ; 
 unsigned int SGMII_AN_RESTART ; 
 int /*<<< orphan*/  SGMSYS_PCS_CONTROL_1 ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

void mtk_sgmii_restart_an(struct mtk_eth *eth, int mac_id)
{
	struct mtk_sgmii *ss = eth->sgmii;
	unsigned int val, sid;

	/* Decide how GMAC and SGMIISYS be mapped */
	sid = (MTK_HAS_CAPS(eth->soc->caps, MTK_SHARED_SGMII)) ?
	       0 : mac_id;

	if (!ss->regmap[sid])
		return;

	regmap_read(ss->regmap[sid], SGMSYS_PCS_CONTROL_1, &val);
	val |= SGMII_AN_RESTART;
	regmap_write(ss->regmap[sid], SGMSYS_PCS_CONTROL_1, val);
}