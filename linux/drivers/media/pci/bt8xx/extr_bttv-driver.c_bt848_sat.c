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
struct bttv {int saturation; int opt_uv_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_E_CONTROL ; 
 int /*<<< orphan*/  BT848_O_CONTROL ; 
 int /*<<< orphan*/  BT848_SAT_U_LO ; 
 int /*<<< orphan*/  BT848_SAT_V_LO ; 
 int /*<<< orphan*/  btaor (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt848_sat(struct bttv *btv, int color)
{
	int val_u,val_v,hibits;

	btv->saturation = color;

	/* 0-511 for the color */
	val_u   = ((color * btv->opt_uv_ratio) / 50) >> 7;
	val_v   = (((color * (100 - btv->opt_uv_ratio) / 50) >>7)*180L)/254;
	hibits  = (val_u >> 7) & 2;
	hibits |= (val_v >> 8) & 1;
	btwrite(val_u & 0xff, BT848_SAT_U_LO);
	btwrite(val_v & 0xff, BT848_SAT_V_LO);
	btaor(hibits, ~3, BT848_E_CONTROL);
	btaor(hibits, ~3, BT848_O_CONTROL);
}