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
struct ufshcd_dme_attr_val {int member_1; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ufshcd_dme_attr_val const*) ; 
 int /*<<< orphan*/  DME_LOCAL ; 
 int /*<<< orphan*/  DME_PEER ; 
 int /*<<< orphan*/  N_DEVICEID ; 
 int /*<<< orphan*/  N_DEVICEID_VALID ; 
 int /*<<< orphan*/  T_CONNECTIONSTATE ; 
 int /*<<< orphan*/  T_CPORTFLAGS ; 
 int /*<<< orphan*/  T_CPORTMODE ; 
 int /*<<< orphan*/  T_PEERCPORTID ; 
 int /*<<< orphan*/  T_PEERDEVICEID ; 
 int /*<<< orphan*/  T_TRAFFICCLASS ; 
 int /*<<< orphan*/  UIC_ARG_MIB (int /*<<< orphan*/ ) ; 
 int ufshcd_dwc_dme_set_attrs (struct ufs_hba*,struct ufshcd_dme_attr_val const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufshcd_dwc_connection_setup(struct ufs_hba *hba)
{
	const struct ufshcd_dme_attr_val setup_attrs[] = {
		{ UIC_ARG_MIB(T_CONNECTIONSTATE), 0, DME_LOCAL },
		{ UIC_ARG_MIB(N_DEVICEID), 0, DME_LOCAL },
		{ UIC_ARG_MIB(N_DEVICEID_VALID), 0, DME_LOCAL },
		{ UIC_ARG_MIB(T_PEERDEVICEID), 1, DME_LOCAL },
		{ UIC_ARG_MIB(T_PEERCPORTID), 0, DME_LOCAL },
		{ UIC_ARG_MIB(T_TRAFFICCLASS), 0, DME_LOCAL },
		{ UIC_ARG_MIB(T_CPORTFLAGS), 0x6, DME_LOCAL },
		{ UIC_ARG_MIB(T_CPORTMODE), 1, DME_LOCAL },
		{ UIC_ARG_MIB(T_CONNECTIONSTATE), 1, DME_LOCAL },
		{ UIC_ARG_MIB(T_CONNECTIONSTATE), 0, DME_PEER },
		{ UIC_ARG_MIB(N_DEVICEID), 1, DME_PEER },
		{ UIC_ARG_MIB(N_DEVICEID_VALID), 1, DME_PEER },
		{ UIC_ARG_MIB(T_PEERDEVICEID), 1, DME_PEER },
		{ UIC_ARG_MIB(T_PEERCPORTID), 0, DME_PEER },
		{ UIC_ARG_MIB(T_TRAFFICCLASS), 0, DME_PEER },
		{ UIC_ARG_MIB(T_CPORTFLAGS), 0x6, DME_PEER },
		{ UIC_ARG_MIB(T_CPORTMODE), 1, DME_PEER },
		{ UIC_ARG_MIB(T_CONNECTIONSTATE), 1, DME_PEER }
	};

	return ufshcd_dwc_dme_set_attrs(hba, setup_attrs, ARRAY_SIZE(setup_attrs));
}