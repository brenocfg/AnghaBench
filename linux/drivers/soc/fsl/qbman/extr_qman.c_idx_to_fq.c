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
typedef  int u32 ;
struct qman_fq {int idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct qman_fq** fq_table ; 
 int num_fqids ; 

__attribute__((used)) static struct qman_fq *idx_to_fq(u32 idx)
{
	struct qman_fq *fq;

#ifdef CONFIG_FSL_DPAA_CHECKING
	if (WARN_ON(idx >= num_fqids * 2))
		return NULL;
#endif
	fq = fq_table[idx];
	DPAA_ASSERT(!fq || idx == fq->idx);

	return fq;
}