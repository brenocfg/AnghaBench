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
typedef  int u16 ;
struct intel_sdvo_connector {int output_flag; } ;
struct intel_sdvo {int dummy; } ;
struct intel_connector {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct intel_sdvo* intel_attached_sdvo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_sdvo_get_active_outputs (struct intel_sdvo*,int*) ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool intel_sdvo_connector_get_hw_state(struct intel_connector *connector)
{
	struct intel_sdvo_connector *intel_sdvo_connector =
		to_intel_sdvo_connector(&connector->base);
	struct intel_sdvo *intel_sdvo = intel_attached_sdvo(&connector->base);
	u16 active_outputs = 0;

	intel_sdvo_get_active_outputs(intel_sdvo, &active_outputs);

	return active_outputs & intel_sdvo_connector->output_flag;
}