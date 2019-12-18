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
struct drm_encoder {int dummy; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  underrun_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_dpu_enc_underrun_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_underrun_callback(struct drm_encoder *drm_enc,
		struct dpu_encoder_phys *phy_enc)
{
	if (!phy_enc)
		return;

	DPU_ATRACE_BEGIN("encoder_underrun_callback");
	atomic_inc(&phy_enc->underrun_cnt);
	trace_dpu_enc_underrun_cb(DRMID(drm_enc),
				  atomic_read(&phy_enc->underrun_cnt));
	DPU_ATRACE_END("encoder_underrun_callback");
}