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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  H_RESET_EVENTS ; 
 int /*<<< orphan*/  ehea_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_reset_events(const u64 adapter_handle, const u64 neq_handle,
			const u64 event_mask)
{
	return ehea_plpar_hcall_norets(H_RESET_EVENTS,
				       adapter_handle,		/* R4 */
				       neq_handle,		/* R5 */
				       event_mask,		/* R6 */
				       0, 0, 0, 0);		/* R7-R12 */
}