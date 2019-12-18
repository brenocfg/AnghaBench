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
struct media_bay_info {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KEYLARGO_FCR1 ; 
 int /*<<< orphan*/  KEYLARGO_MBCR ; 
 int /*<<< orphan*/  KL1_EIDE0_ENABLE ; 
 int /*<<< orphan*/  KL1_EIDE0_RESET_N ; 
 int /*<<< orphan*/  KL_MBCR_MB0_IDE_ENABLE ; 
 int /*<<< orphan*/  KL_MBCR_MB0_PCI_ENABLE ; 
 int /*<<< orphan*/  KL_MBCR_MB0_SOUND_ENABLE ; 
 int /*<<< orphan*/  MB_BIC (struct media_bay_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_BIS (struct media_bay_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MB_CD 130 
#define  MB_PCI 129 
#define  MB_SOUND 128 

__attribute__((used)) static int
keylargo_mb_setup_bus(struct media_bay_info* bay, u8 device_id)
{
	switch(device_id) {
		case MB_CD:
			MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_IDE_ENABLE);
			MB_BIC(bay, KEYLARGO_FCR1, KL1_EIDE0_RESET_N);
			MB_BIS(bay, KEYLARGO_FCR1, KL1_EIDE0_ENABLE);
			return 0;
		case MB_PCI:
			MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_PCI_ENABLE);
			return 0;
		case MB_SOUND:
			MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_SOUND_ENABLE);
			return 0;
	}
	return -ENODEV;
}