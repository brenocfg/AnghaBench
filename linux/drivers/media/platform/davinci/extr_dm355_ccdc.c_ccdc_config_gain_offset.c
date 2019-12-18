#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  b_mg; int /*<<< orphan*/  gb_g; int /*<<< orphan*/  gr_cy; int /*<<< orphan*/  r_ye; } ;
struct TYPE_5__ {int /*<<< orphan*/  ccdc_offset; TYPE_1__ gain; } ;
struct TYPE_6__ {TYPE_2__ bayer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMGGAIN ; 
 int /*<<< orphan*/  GBGGAIN ; 
 int /*<<< orphan*/  GRCYGAIN ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  RYEGAIN ; 
 TYPE_3__ ccdc_cfg ; 
 int /*<<< orphan*/  regw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_config_gain_offset(void)
{
	/* configure gain */
	regw(ccdc_cfg.bayer.gain.r_ye, RYEGAIN);
	regw(ccdc_cfg.bayer.gain.gr_cy, GRCYGAIN);
	regw(ccdc_cfg.bayer.gain.gb_g, GBGGAIN);
	regw(ccdc_cfg.bayer.gain.b_mg, BMGGAIN);
	/* configure offset */
	regw(ccdc_cfg.bayer.ccdc_offset, OFFSET);
}