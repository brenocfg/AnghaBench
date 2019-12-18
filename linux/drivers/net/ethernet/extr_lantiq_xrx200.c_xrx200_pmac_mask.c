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
typedef  int /*<<< orphan*/  u32 ;
struct xrx200_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xrx200_pmac_r32 (struct xrx200_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xrx200_pmac_w32 (struct xrx200_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xrx200_pmac_mask(struct xrx200_priv *priv, u32 clear, u32 set,
			     u32 offset)
{
	u32 val = xrx200_pmac_r32(priv, offset);

	val &= ~(clear);
	val |= set;
	xrx200_pmac_w32(priv, val, offset);
}