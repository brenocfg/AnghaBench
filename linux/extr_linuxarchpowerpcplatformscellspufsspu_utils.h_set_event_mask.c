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

/* Variables and functions */
 int /*<<< orphan*/  SPU_WrEventMask ; 
 int /*<<< orphan*/  spu_writech (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void set_event_mask(void)
{
	unsigned int event_mask = 0;

	/* Save, Step 4:
	 * Restore, Step 1:
	 *    Set the SPU_RdEventMsk channel to zero to mask
	 *    all events.
	 */
	spu_writech(SPU_WrEventMask, event_mask);
}