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
typedef  int u8 ;
struct sis_video_info {scalar_t__ sisvga_engine; } ;

/* Variables and functions */
 int IND_SIS_MODULE_ENABLE ; 
 int IND_SIS_PCI_ADDRESS_SET ; 
 int /*<<< orphan*/  SISSR ; 
 scalar_t__ SIS_300_VGA ; 
 scalar_t__ SIS_315_VGA ; 
 int SIS_MEM_MAP_IO_ENABLE ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sisfb_syncaccel (struct sis_video_info*) ; 

__attribute__((used)) static void
sisfb_check_engine_and_sync(struct sis_video_info *ivideo)
{
	u8 cr30, cr31;

	/* Check if MMIO and engines are enabled,
	 * and sync in case they are. Can't use
	 * ivideo->accel here, as this might have
	 * been changed before this is called.
	 */
	cr30 = SiS_GetReg(SISSR, IND_SIS_PCI_ADDRESS_SET);
	cr31 = SiS_GetReg(SISSR, IND_SIS_MODULE_ENABLE);
	/* MMIO and 2D/3D engine enabled? */
	if((cr30 & SIS_MEM_MAP_IO_ENABLE) && (cr31 & 0x42)) {
#ifdef CONFIG_FB_SIS_300
		if(ivideo->sisvga_engine == SIS_300_VGA) {
			/* Don't care about TurboQueue. It's
			 * enough to know that the engines
			 * are enabled
			 */
			sisfb_syncaccel(ivideo);
		}
#endif
#ifdef CONFIG_FB_SIS_315
		if(ivideo->sisvga_engine == SIS_315_VGA) {
			/* Check that any queue mode is
			 * enabled, and that the queue
			 * is not in the state of "reset"
			 */
			cr30 = SiS_GetReg(SISSR, 0x26);
			if((cr30 & 0xe0) && (!(cr30 & 0x01))) {
				sisfb_syncaccel(ivideo);
			}
		}
#endif
	}
}