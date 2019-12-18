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
struct intel_dsi {scalar_t__ operation_mode; } ;

/* Variables and functions */
 scalar_t__ INTEL_DSI_COMMAND_MODE ; 

__attribute__((used)) static inline bool is_cmd_mode(struct intel_dsi *intel_dsi)
{
	return intel_dsi->operation_mode == INTEL_DSI_COMMAND_MODE;
}