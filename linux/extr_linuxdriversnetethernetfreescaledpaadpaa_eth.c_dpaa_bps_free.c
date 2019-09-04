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
struct dpaa_priv {int /*<<< orphan*/ * dpaa_bps; } ;

/* Variables and functions */
 int DPAA_BPS_NUM ; 
 int /*<<< orphan*/  dpaa_bp_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpaa_bps_free(struct dpaa_priv *priv)
{
	int i;

	for (i = 0; i < DPAA_BPS_NUM; i++)
		dpaa_bp_free(priv->dpaa_bps[i]);
}