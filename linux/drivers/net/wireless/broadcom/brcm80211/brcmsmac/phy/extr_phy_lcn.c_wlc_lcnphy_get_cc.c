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
typedef  int u8 ;
typedef  int u16 ;
struct lcnphy_unsign16_struct {int re; int im; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_lcnphy_get_radio_loft (struct brcms_phy*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_iqcc (struct brcms_phy*,int*,int*) ; 
 int wlc_lcnphy_get_tx_locc (struct brcms_phy*) ; 

__attribute__((used)) static struct lcnphy_unsign16_struct
wlc_lcnphy_get_cc(struct brcms_phy *pi, int cal_type)
{
	u16 a, b, didq;
	u8 di0, dq0, ei, eq, fi, fq;
	struct lcnphy_unsign16_struct cc;
	cc.re = 0;
	cc.im = 0;
	switch (cal_type) {
	case 0:
		wlc_lcnphy_get_tx_iqcc(pi, &a, &b);
		cc.re = a;
		cc.im = b;
		break;
	case 2:
		didq = wlc_lcnphy_get_tx_locc(pi);
		di0 = (((didq & 0xff00) << 16) >> 24);
		dq0 = (((didq & 0x00ff) << 24) >> 24);
		cc.re = (u16) di0;
		cc.im = (u16) dq0;
		break;
	case 3:
		wlc_lcnphy_get_radio_loft(pi, &ei, &eq, &fi, &fq);
		cc.re = (u16) ei;
		cc.im = (u16) eq;
		break;
	case 4:
		wlc_lcnphy_get_radio_loft(pi, &ei, &eq, &fi, &fq);
		cc.re = (u16) fi;
		cc.im = (u16) fq;
		break;
	}
	return cc;
}