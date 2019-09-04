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
struct dpu_encoder_phys {scalar_t__ topology_name; } ;

/* Variables and functions */
 scalar_t__ DPU_RM_TOPOLOGY_DUALPIPE ; 

__attribute__((used)) static bool _dpu_encoder_phys_is_dual_ctl(struct dpu_encoder_phys *phys_enc)
{
	if (!phys_enc)
		return false;

	if (phys_enc->topology_name == DPU_RM_TOPOLOGY_DUALPIPE)
		return true;

	return false;
}