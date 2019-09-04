#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {unsigned int ri_mask; unsigned int ri; } ;

/* Variables and functions */

__attribute__((used)) static void mvpp2_prs_shadow_ri_set(struct mvpp2 *priv, int index,
				    unsigned int ri, unsigned int ri_mask)
{
	priv->prs_shadow[index].ri_mask = ri_mask;
	priv->prs_shadow[index].ri = ri;
}