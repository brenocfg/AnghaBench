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
typedef  int u32 ;
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_WFODP ; 
 int /*<<< orphan*/  JME_WFOI ; 
 int WAKEUP_FRAME_MASK_DWNR ; 
 int WFOI_CRC_SEL ; 
 int WFOI_FRAME_SEL ; 
 int WFOI_MASK_SEL ; 
 int WFOI_MASK_SHIFT ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
jme_setup_wakeup_frame(struct jme_adapter *jme,
		       const u32 *mask, u32 crc, int fnr)
{
	int i;

	/*
	 * Setup CRC pattern
	 */
	jwrite32(jme, JME_WFOI, WFOI_CRC_SEL | (fnr & WFOI_FRAME_SEL));
	wmb();
	jwrite32(jme, JME_WFODP, crc);
	wmb();

	/*
	 * Setup Mask
	 */
	for (i = 0 ; i < WAKEUP_FRAME_MASK_DWNR ; ++i) {
		jwrite32(jme, JME_WFOI,
				((i << WFOI_MASK_SHIFT) & WFOI_MASK_SEL) |
				(fnr & WFOI_FRAME_SEL));
		wmb();
		jwrite32(jme, JME_WFODP, mask[i]);
		wmb();
	}
}