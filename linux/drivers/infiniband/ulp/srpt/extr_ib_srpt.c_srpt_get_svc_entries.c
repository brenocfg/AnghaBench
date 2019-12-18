#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct ib_dm_svc_entries {TYPE_1__* service_entries; } ;
struct TYPE_4__ {void* status; } ;
struct ib_dm_mad {TYPE_2__ mad_hdr; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_MAD_STATUS_INVALID_FIELD ; 
 int /*<<< orphan*/  DM_MAD_STATUS_NO_IOC ; 
 char* SRP_SERVICE_NAME_PREFIX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_dm_svc_entries*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srpt_get_svc_entries(u64 ioc_guid,
				 u16 slot, u8 hi, u8 lo, struct ib_dm_mad *mad)
{
	struct ib_dm_svc_entries *svc_entries;

	WARN_ON(!ioc_guid);

	if (!slot || slot > 16) {
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_INVALID_FIELD);
		return;
	}

	if (slot > 2 || lo > hi || hi > 1) {
		mad->mad_hdr.status
			= cpu_to_be16(DM_MAD_STATUS_NO_IOC);
		return;
	}

	svc_entries = (struct ib_dm_svc_entries *)mad->data;
	memset(svc_entries, 0, sizeof(*svc_entries));
	svc_entries->service_entries[0].id = cpu_to_be64(ioc_guid);
	snprintf(svc_entries->service_entries[0].name,
		 sizeof(svc_entries->service_entries[0].name),
		 "%s%016llx",
		 SRP_SERVICE_NAME_PREFIX,
		 ioc_guid);

	mad->mad_hdr.status = 0;
}