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
typedef  scalar_t__ u64 ;
struct perf_output_handle {int /*<<< orphan*/  head; } ;
struct arm_spe_pmu_buf {int /*<<< orphan*/  snapshot; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SPE_BUF_PAD_BYTE ; 
 scalar_t__ PERF_IDX2OFF (int /*<<< orphan*/ ,struct arm_spe_pmu_buf*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_aux_output_skip (struct perf_output_handle*,int) ; 
 struct arm_spe_pmu_buf* perf_get_aux (struct perf_output_handle*) ; 

__attribute__((used)) static void arm_spe_pmu_pad_buf(struct perf_output_handle *handle, int len)
{
	struct arm_spe_pmu_buf *buf = perf_get_aux(handle);
	u64 head = PERF_IDX2OFF(handle->head, buf);

	memset(buf->base + head, ARM_SPE_BUF_PAD_BYTE, len);
	if (!buf->snapshot)
		perf_aux_output_skip(handle, len);
}