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
 int /*<<< orphan*/  SPU_SAVE_COMPLETE ; 
 int /*<<< orphan*/  spu_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void save_complete(void)
{
	/* Save, Step 18:
	 *    Issue a stop-and-signal instruction indicating
	 *    "save complete".  Note: This function will not
	 *    return!!
	 */
	spu_stop(SPU_SAVE_COMPLETE);
}