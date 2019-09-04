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
typedef  int u32 ;
struct bgmac {int feature_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGMAC_CMDCFG ; 
 int BGMAC_CMDCFG_SR_REV0 ; 
 int BGMAC_CMDCFG_SR_REV4 ; 
 int BGMAC_FEAT_CMDCFG_SR_REV4 ; 
 int /*<<< orphan*/  bgmac_mask (struct bgmac*,int /*<<< orphan*/ ,int) ; 
 int bgmac_read (struct bgmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgmac_set (struct bgmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bgmac_cmdcfg_maskset(struct bgmac *bgmac, u32 mask, u32 set,
				 bool force)
{
	u32 cmdcfg = bgmac_read(bgmac, BGMAC_CMDCFG);
	u32 new_val = (cmdcfg & mask) | set;
	u32 cmdcfg_sr;

	if (bgmac->feature_flags & BGMAC_FEAT_CMDCFG_SR_REV4)
		cmdcfg_sr = BGMAC_CMDCFG_SR_REV4;
	else
		cmdcfg_sr = BGMAC_CMDCFG_SR_REV0;

	bgmac_set(bgmac, BGMAC_CMDCFG, cmdcfg_sr);
	udelay(2);

	if (new_val != cmdcfg || force)
		bgmac_write(bgmac, BGMAC_CMDCFG, new_val);

	bgmac_mask(bgmac, BGMAC_CMDCFG, ~cmdcfg_sr);
	udelay(2);
}