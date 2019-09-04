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
struct lmac {int /*<<< orphan*/  lmacid; } ;
struct bgx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGX_CMRX_CFG ; 
 int bgx_reg_read (struct bgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 bgx_get_lane2sds_cfg(struct bgx *bgx, struct lmac *lmac)
{
	return (u8)(bgx_reg_read(bgx, lmac->lmacid, BGX_CMRX_CFG) & 0xFF);
}