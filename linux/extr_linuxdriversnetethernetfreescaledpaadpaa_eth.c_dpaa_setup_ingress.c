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
struct dpaa_priv {int /*<<< orphan*/  channel; int /*<<< orphan*/  net_dev; } ;
struct dpaa_fq {int /*<<< orphan*/  channel; int /*<<< orphan*/  flags; int /*<<< orphan*/  net_dev; struct qman_fq fq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMAN_FQ_FLAG_NO_ENQUEUE ; 

__attribute__((used)) static inline void dpaa_setup_ingress(const struct dpaa_priv *priv,
				      struct dpaa_fq *fq,
				      const struct qman_fq *template)
{
	fq->fq_base = *template;
	fq->net_dev = priv->net_dev;

	fq->flags = QMAN_FQ_FLAG_NO_ENQUEUE;
	fq->channel = priv->channel;
}