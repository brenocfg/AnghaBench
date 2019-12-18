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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_kms {int dummy; } ;
struct msm_format {int dummy; } ;
struct dpu_format {struct msm_format const base; } ;

/* Variables and functions */
 struct dpu_format* dpu_get_dpu_format_ext (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

const struct msm_format *dpu_get_msm_format(
		struct msm_kms *kms,
		const uint32_t format,
		const uint64_t modifiers)
{
	const struct dpu_format *fmt = dpu_get_dpu_format_ext(format,
			modifiers);
	if (fmt)
		return &fmt->base;
	return NULL;
}