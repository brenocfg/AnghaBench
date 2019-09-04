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
typedef  int /*<<< orphan*/  u16 ;
struct psb_intel_sdvo {int dummy; } ;
typedef  int /*<<< orphan*/  outputs ;

/* Variables and functions */
 int /*<<< orphan*/  SDVO_CMD_SET_TARGET_OUTPUT ; 
 int psb_intel_sdvo_set_value (struct psb_intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool psb_intel_sdvo_set_target_output(struct psb_intel_sdvo *psb_intel_sdvo,
					 u16 outputs)
{
	return psb_intel_sdvo_set_value(psb_intel_sdvo,
				    SDVO_CMD_SET_TARGET_OUTPUT,
				    &outputs, sizeof(outputs));
}