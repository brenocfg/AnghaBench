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
typedef  int /*<<< orphan*/  u8 ;
struct smu_sdbp_slotspow {int dummy; } ;
struct smu_sdbp_header {int /*<<< orphan*/  version; } ;
struct smu_sdbp_cpuvcp {int dummy; } ;
struct smu_sdbp_cpudiode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_SDB_CPUDIODE_ID ; 
 int /*<<< orphan*/  SMU_SDB_CPUVCP_ID ; 
 int /*<<< orphan*/  SMU_SDB_DEBUG_SWITCHES_ID ; 
 int /*<<< orphan*/  SMU_SDB_SLOTSPOW_ID ; 
 struct smu_sdbp_cpudiode* cpudiode ; 
 struct smu_sdbp_cpuvcp* cpuvcp ; 
 int /*<<< orphan*/  cpuvcp_version ; 
 int /*<<< orphan*/ * debugswitches ; 
 struct smu_sdbp_slotspow* slotspow ; 
 struct smu_sdbp_header* smu_get_sdb_partition (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smu_fetch_param_partitions(void)
{
	const struct smu_sdbp_header *hdr;

	/* Get CPU voltage/current/power calibration data */
	hdr = smu_get_sdb_partition(SMU_SDB_CPUVCP_ID, NULL);
	if (hdr != NULL) {
		cpuvcp = (struct smu_sdbp_cpuvcp *)&hdr[1];
		/* Keep version around */
		cpuvcp_version = hdr->version;
	}

	/* Get CPU diode calibration data */
	hdr = smu_get_sdb_partition(SMU_SDB_CPUDIODE_ID, NULL);
	if (hdr != NULL)
		cpudiode = (struct smu_sdbp_cpudiode *)&hdr[1];

	/* Get slots power calibration data if any */
	hdr = smu_get_sdb_partition(SMU_SDB_SLOTSPOW_ID, NULL);
	if (hdr != NULL)
		slotspow = (struct smu_sdbp_slotspow *)&hdr[1];

	/* Get debug switches if any */
	hdr = smu_get_sdb_partition(SMU_SDB_DEBUG_SWITCHES_ID, NULL);
	if (hdr != NULL)
		debugswitches = (u8 *)&hdr[1];
}