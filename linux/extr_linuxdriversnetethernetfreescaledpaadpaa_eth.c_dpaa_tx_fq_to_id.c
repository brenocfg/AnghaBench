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
struct qman_fq {int dummy; } ;
struct dpaa_priv {struct qman_fq** egress_fqs; } ;

/* Variables and functions */
 int DPAA_ETH_TXQ_NUM ; 
 int EINVAL ; 

__attribute__((used)) static inline int dpaa_tx_fq_to_id(const struct dpaa_priv *priv,
				   struct qman_fq *tx_fq)
{
	int i;

	for (i = 0; i < DPAA_ETH_TXQ_NUM; i++)
		if (priv->egress_fqs[i] == tx_fq)
			return i;

	return -EINVAL;
}