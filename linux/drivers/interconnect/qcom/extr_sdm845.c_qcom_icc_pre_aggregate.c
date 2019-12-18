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
struct qcom_icc_node {scalar_t__* max_peak; scalar_t__* sum_avg; } ;
struct icc_node {struct qcom_icc_node* data; } ;

/* Variables and functions */
 size_t QCOM_ICC_NUM_BUCKETS ; 

__attribute__((used)) static void qcom_icc_pre_aggregate(struct icc_node *node)
{
	size_t i;
	struct qcom_icc_node *qn;

	qn = node->data;

	for (i = 0; i < QCOM_ICC_NUM_BUCKETS; i++) {
		qn->sum_avg[i] = 0;
		qn->max_peak[i] = 0;
	}
}