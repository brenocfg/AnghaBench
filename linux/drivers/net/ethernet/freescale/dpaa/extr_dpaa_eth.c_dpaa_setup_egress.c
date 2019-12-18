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
typedef  scalar_t__ u16 ;
struct qman_fq {int dummy; } ;
struct fman_port {int dummy; } ;
struct dpaa_priv {int /*<<< orphan*/  net_dev; } ;
struct dpaa_fq {int /*<<< orphan*/  flags; scalar_t__ channel; int /*<<< orphan*/  net_dev; struct qman_fq fq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMAN_FQ_FLAG_NO_MODIFY ; 
 int /*<<< orphan*/  QMAN_FQ_FLAG_TO_DCPORTAL ; 
 scalar_t__ fman_port_get_qman_channel_id (struct fman_port*) ; 

__attribute__((used)) static inline void dpaa_setup_egress(const struct dpaa_priv *priv,
				     struct dpaa_fq *fq,
				     struct fman_port *port,
				     const struct qman_fq *template)
{
	fq->fq_base = *template;
	fq->net_dev = priv->net_dev;

	if (port) {
		fq->flags = QMAN_FQ_FLAG_TO_DCPORTAL;
		fq->channel = (u16)fman_port_get_qman_channel_id(port);
	} else {
		fq->flags = QMAN_FQ_FLAG_NO_MODIFY;
	}
}