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
struct mantis_pci {int subsystem_device; int /*<<< orphan*/ * hwconfig; } ;

/* Variables and functions */
#define  CINERGY_C 136 
#define  MANTIS_VP_1033_DVB_S 135 
#define  MANTIS_VP_1034_DVB_S 134 
#define  MANTIS_VP_1041_DVB_S2 133 
#define  MANTIS_VP_2033_DVB_C 132 
#define  MANTIS_VP_2040_DVB_C 131 
#define  MANTIS_VP_3030_DVB_T 130 
#define  TECHNISAT_CABLESTAR_HD2 129 
#define  TECHNISAT_SKYSTAR_HD2 128 
 int /*<<< orphan*/  unknown_device ; 
 int /*<<< orphan*/  vp1033_mantis_config ; 
 int /*<<< orphan*/  vp1034_mantis_config ; 
 int /*<<< orphan*/  vp1041_mantis_config ; 
 int /*<<< orphan*/  vp2033_mantis_config ; 
 int /*<<< orphan*/  vp2040_mantis_config ; 
 int /*<<< orphan*/  vp3030_mantis_config ; 

__attribute__((used)) static void mantis_load_config(struct mantis_pci *mantis)
{
	switch (mantis->subsystem_device) {
	case MANTIS_VP_1033_DVB_S:	/* VP-1033 */
		mantis->hwconfig = &vp1033_mantis_config;
		break;
	case MANTIS_VP_1034_DVB_S:	/* VP-1034 */
		mantis->hwconfig = &vp1034_mantis_config;
		break;
	case MANTIS_VP_1041_DVB_S2:	/* VP-1041 */
	case TECHNISAT_SKYSTAR_HD2:
		mantis->hwconfig = &vp1041_mantis_config;
		break;
	case MANTIS_VP_2033_DVB_C:	/* VP-2033 */
		mantis->hwconfig = &vp2033_mantis_config;
		break;
	case MANTIS_VP_2040_DVB_C:	/* VP-2040 */
	case CINERGY_C:	/* VP-2040 clone */
	case TECHNISAT_CABLESTAR_HD2:
		mantis->hwconfig = &vp2040_mantis_config;
		break;
	case MANTIS_VP_3030_DVB_T:	/* VP-3030 */
		mantis->hwconfig = &vp3030_mantis_config;
		break;
	default:
		mantis->hwconfig = &unknown_device;
		break;
	}
}