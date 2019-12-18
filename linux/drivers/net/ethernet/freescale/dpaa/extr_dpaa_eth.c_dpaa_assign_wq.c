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
struct dpaa_fq {int fq_type; int wq; int /*<<< orphan*/  fqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ETH_TXQ_NUM ; 
 int DPAA_TC_TXQ_NUM ; 
#define  FQ_TYPE_RX_DEFAULT 134 
#define  FQ_TYPE_RX_ERROR 133 
#define  FQ_TYPE_RX_PCD 132 
#define  FQ_TYPE_TX 131 
#define  FQ_TYPE_TX_CONFIRM 130 
#define  FQ_TYPE_TX_CONF_MQ 129 
#define  FQ_TYPE_TX_ERROR 128 
 int /*<<< orphan*/  WARN (int,char*,int,...) ; 

__attribute__((used)) static inline void dpaa_assign_wq(struct dpaa_fq *fq, int idx)
{
	switch (fq->fq_type) {
	case FQ_TYPE_TX_CONFIRM:
	case FQ_TYPE_TX_CONF_MQ:
		fq->wq = 1;
		break;
	case FQ_TYPE_RX_ERROR:
	case FQ_TYPE_TX_ERROR:
		fq->wq = 5;
		break;
	case FQ_TYPE_RX_DEFAULT:
	case FQ_TYPE_RX_PCD:
		fq->wq = 6;
		break;
	case FQ_TYPE_TX:
		switch (idx / DPAA_TC_TXQ_NUM) {
		case 0:
			/* Low priority (best effort) */
			fq->wq = 6;
			break;
		case 1:
			/* Medium priority */
			fq->wq = 2;
			break;
		case 2:
			/* High priority */
			fq->wq = 1;
			break;
		case 3:
			/* Very high priority */
			fq->wq = 0;
			break;
		default:
			WARN(1, "Too many TX FQs: more than %d!\n",
			     DPAA_ETH_TXQ_NUM);
		}
		break;
	default:
		WARN(1, "Invalid FQ type %d for FQID %d!\n",
		     fq->fq_type, fq->fqid);
	}
}