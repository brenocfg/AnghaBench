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
struct nvec_chip {int dummy; } ;

/* Variables and functions */
 int GLOBAL_EVENTS ; 
 int NVEC_SLEEP ; 
 int /*<<< orphan*/  nvec_write_async (struct nvec_chip*,unsigned char*,int) ; 

__attribute__((used)) static void nvec_toggle_global_events(struct nvec_chip *nvec, bool state)
{
	unsigned char global_events[] = { NVEC_SLEEP, GLOBAL_EVENTS, state };

	nvec_write_async(nvec, global_events, 3);
}