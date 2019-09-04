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
struct cs2000_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FUNC_CFG1 ; 
 int /*<<< orphan*/  REFCLKDIV (int) ; 
 int /*<<< orphan*/  REFCLKDIV_MASK ; 
 int cs2000_bset (struct cs2000_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs2000_clk_in_bound_rate(struct cs2000_priv *priv,
				    u32 rate_in)
{
	u32 val;

	if (rate_in >= 32000000 && rate_in < 56000000)
		val = 0x0;
	else if (rate_in >= 16000000 && rate_in < 28000000)
		val = 0x1;
	else if (rate_in >= 8000000 && rate_in < 14000000)
		val = 0x2;
	else
		return -EINVAL;

	return cs2000_bset(priv, FUNC_CFG1,
			   REFCLKDIV_MASK,
			   REFCLKDIV(val));
}