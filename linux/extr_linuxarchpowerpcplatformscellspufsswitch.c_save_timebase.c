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
struct spu_state {int /*<<< orphan*/  suspend_time; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cycles () ; 

__attribute__((used)) static inline void save_timebase(struct spu_state *csa, struct spu *spu)
{
	/* Save, Step 14:
	 *    Read PPE Timebase High and Timebase low registers
	 *    and save in CSA.  TBD.
	 */
	csa->suspend_time = get_cycles();
}