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
struct ipw2100_priv {int /*<<< orphan*/ ** snapshot; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw2100_snapshot_free(struct ipw2100_priv *priv)
{
	int i;
	if (!priv->snapshot[0])
		return;
	for (i = 0; i < 0x30; i++)
		kfree(priv->snapshot[i]);
	priv->snapshot[0] = NULL;
}