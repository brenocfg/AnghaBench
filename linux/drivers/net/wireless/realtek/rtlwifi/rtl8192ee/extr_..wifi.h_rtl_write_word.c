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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* read16_sync ) (struct rtl_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write16_async ) (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct rtl_priv {TYPE_2__ io; TYPE_1__* cfg; } ;
struct TYPE_3__ {scalar_t__ write_readback; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rtl_write_word(struct rtl_priv *rtlpriv, u32 addr, u16 val16)
{
	rtlpriv->io.write16_async(rtlpriv, addr, val16);

	if (rtlpriv->cfg->write_readback)
		rtlpriv->io.read16_sync(rtlpriv, addr);
}