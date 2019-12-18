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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
typedef  enum cxgb4_bar2_qtype { ____Placeholder_cxgb4_bar2_qtype } cxgb4_bar2_qtype ;

/* Variables and functions */
 int CXGB4_BAR2_QTYPE_EGRESS ; 
 int /*<<< orphan*/  T4_BAR2_QTYPE_EGRESS ; 
 int /*<<< orphan*/  T4_BAR2_QTYPE_INGRESS ; 
 int /*<<< orphan*/  netdev2adap (struct net_device*) ; 
 int t4_bar2_sge_qregs (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int*) ; 

int cxgb4_bar2_sge_qregs(struct net_device *dev,
			 unsigned int qid,
			 enum cxgb4_bar2_qtype qtype,
			 int user,
			 u64 *pbar2_qoffset,
			 unsigned int *pbar2_qid)
{
	return t4_bar2_sge_qregs(netdev2adap(dev),
				 qid,
				 (qtype == CXGB4_BAR2_QTYPE_EGRESS
				  ? T4_BAR2_QTYPE_EGRESS
				  : T4_BAR2_QTYPE_INGRESS),
				 user,
				 pbar2_qoffset,
				 pbar2_qid);
}