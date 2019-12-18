#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ ant_num; } ;
struct TYPE_4__ {TYPE_1__ btc_info; } ;
struct rtl_priv {TYPE_2__ btcoexist; } ;

/* Variables and functions */
 scalar_t__ ANT_X2 ; 

__attribute__((used)) static u8 rtl_get_hwpg_ant_num(struct rtl_priv *rtlpriv)
{
	u8 num;

	if (rtlpriv->btcoexist.btc_info.ant_num == ANT_X2)
		num = 2;
	else
		num = 1;

	return num;
}