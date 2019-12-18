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
struct TYPE_2__ {int valid; int lu; } ;

/* Variables and functions */

__attribute__((used)) static void mvpp2_prs_shadow_set(struct mvpp2 *priv, int index, int lu)
{
	priv->prs_shadow[index].valid = true;
	priv->prs_shadow[index].lu = lu;
}