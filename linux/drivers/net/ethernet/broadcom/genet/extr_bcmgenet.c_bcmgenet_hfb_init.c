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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ GENET_IS_V1 (struct bcmgenet_priv*) ; 
 scalar_t__ GENET_IS_V2 (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_hfb_clear (struct bcmgenet_priv*) ; 

__attribute__((used)) static void bcmgenet_hfb_init(struct bcmgenet_priv *priv)
{
	if (GENET_IS_V1(priv) || GENET_IS_V2(priv))
		return;

	bcmgenet_hfb_clear(priv);
}