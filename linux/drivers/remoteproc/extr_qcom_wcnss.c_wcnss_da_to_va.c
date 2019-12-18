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
typedef  int u64 ;
struct rproc {scalar_t__ priv; } ;
struct qcom_wcnss {int mem_reloc; int mem_size; void* mem_region; } ;

/* Variables and functions */

__attribute__((used)) static void *wcnss_da_to_va(struct rproc *rproc, u64 da, int len)
{
	struct qcom_wcnss *wcnss = (struct qcom_wcnss *)rproc->priv;
	int offset;

	offset = da - wcnss->mem_reloc;
	if (offset < 0 || offset + len > wcnss->mem_size)
		return NULL;

	return wcnss->mem_region + offset;
}