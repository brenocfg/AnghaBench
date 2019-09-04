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
struct bttv_geometry {int vtc; int hscale; int vscale; int width; int hdelay; int sheight; int vdelay; int crop; int vtotal; scalar_t__ comb; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
 scalar_t__ BT848_E_CROP ; 
 scalar_t__ BT848_E_HACTIVE_LO ; 
 scalar_t__ BT848_E_HDELAY_LO ; 
 scalar_t__ BT848_E_HSCALE_HI ; 
 scalar_t__ BT848_E_HSCALE_LO ; 
 scalar_t__ BT848_E_VACTIVE_LO ; 
 scalar_t__ BT848_E_VDELAY_LO ; 
 scalar_t__ BT848_E_VSCALE_HI ; 
 scalar_t__ BT848_E_VSCALE_LO ; 
 scalar_t__ BT848_E_VTC ; 
 int /*<<< orphan*/  BT848_VSCALE_COMB ; 
 scalar_t__ BT848_VTOTAL_HI ; 
 scalar_t__ BT848_VTOTAL_LO ; 
 int /*<<< orphan*/  btand (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btaor (int,int,scalar_t__) ; 
 int /*<<< orphan*/  btor (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btwrite (int,scalar_t__) ; 

__attribute__((used)) static void
bttv_apply_geo(struct bttv *btv, struct bttv_geometry *geo, int odd)
{
	int off = odd ? 0x80 : 0x00;

	if (geo->comb)
		btor(BT848_VSCALE_COMB, BT848_E_VSCALE_HI+off);
	else
		btand(~BT848_VSCALE_COMB, BT848_E_VSCALE_HI+off);

	btwrite(geo->vtc,             BT848_E_VTC+off);
	btwrite(geo->hscale >> 8,     BT848_E_HSCALE_HI+off);
	btwrite(geo->hscale & 0xff,   BT848_E_HSCALE_LO+off);
	btaor((geo->vscale>>8), 0xe0, BT848_E_VSCALE_HI+off);
	btwrite(geo->vscale & 0xff,   BT848_E_VSCALE_LO+off);
	btwrite(geo->width & 0xff,    BT848_E_HACTIVE_LO+off);
	btwrite(geo->hdelay & 0xff,   BT848_E_HDELAY_LO+off);
	btwrite(geo->sheight & 0xff,  BT848_E_VACTIVE_LO+off);
	btwrite(geo->vdelay & 0xff,   BT848_E_VDELAY_LO+off);
	btwrite(geo->crop,            BT848_E_CROP+off);
	btwrite(geo->vtotal>>8,       BT848_VTOTAL_HI);
	btwrite(geo->vtotal & 0xff,   BT848_VTOTAL_LO);
}