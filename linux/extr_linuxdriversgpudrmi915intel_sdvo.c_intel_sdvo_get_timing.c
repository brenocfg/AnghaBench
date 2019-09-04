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
typedef  scalar_t__ u8 ;
struct intel_sdvo_dtd {int /*<<< orphan*/  part2; int /*<<< orphan*/  part1; } ;
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 scalar_t__ intel_sdvo_get_value (struct intel_sdvo*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool intel_sdvo_get_timing(struct intel_sdvo *intel_sdvo, u8 cmd,
				  struct intel_sdvo_dtd *dtd)
{
	return intel_sdvo_get_value(intel_sdvo, cmd, &dtd->part1, sizeof(dtd->part1)) &&
		intel_sdvo_get_value(intel_sdvo, cmd + 1, &dtd->part2, sizeof(dtd->part2));
}