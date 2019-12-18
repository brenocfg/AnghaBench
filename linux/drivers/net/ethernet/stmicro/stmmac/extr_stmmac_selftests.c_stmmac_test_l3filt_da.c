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
struct stmmac_priv {int dummy; } ;

/* Variables and functions */
 int __stmmac_test_l3filt (struct stmmac_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmac_test_l3filt_da(struct stmmac_priv *priv)
{
	u32 addr = 0x10203040;

	return __stmmac_test_l3filt(priv, addr, 0, ~0, 0);
}