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
struct dpaa2_eth_priv {int /*<<< orphan*/  enqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_ENQUEUE_FQID_VER_MAJOR ; 
 int /*<<< orphan*/  DPNI_ENQUEUE_FQID_VER_MINOR ; 
 scalar_t__ dpaa2_eth_cmp_dpni_ver (struct dpaa2_eth_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_eth_enqueue_fq ; 
 int /*<<< orphan*/  dpaa2_eth_enqueue_qd ; 

__attribute__((used)) static void set_enqueue_mode(struct dpaa2_eth_priv *priv)
{
	if (dpaa2_eth_cmp_dpni_ver(priv, DPNI_ENQUEUE_FQID_VER_MAJOR,
				   DPNI_ENQUEUE_FQID_VER_MINOR) < 0)
		priv->enqueue = dpaa2_eth_enqueue_qd;
	else
		priv->enqueue = dpaa2_eth_enqueue_fq;
}