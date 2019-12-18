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
struct dpu_encoder_phys {size_t intf_idx; } ;
struct dpu_encoder_hw_resources {int /*<<< orphan*/ * intfs; } ;

/* Variables and functions */
 size_t INTF_0 ; 
 int /*<<< orphan*/  INTF_MODE_VIDEO ; 

__attribute__((used)) static void dpu_encoder_phys_vid_get_hw_resources(
		struct dpu_encoder_phys *phys_enc,
		struct dpu_encoder_hw_resources *hw_res)
{
	hw_res->intfs[phys_enc->intf_idx - INTF_0] = INTF_MODE_VIDEO;
}