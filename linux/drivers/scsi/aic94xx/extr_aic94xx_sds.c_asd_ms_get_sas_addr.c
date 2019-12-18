#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct asd_manuf_sec {int /*<<< orphan*/  sas_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  sas_addr; } ;
struct asd_ha_struct {TYPE_1__ hw_prof; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_ms_get_sas_addr(struct asd_ha_struct *asd_ha,
			       struct asd_manuf_sec *ms)
{
	memcpy(asd_ha->hw_prof.sas_addr, ms->sas_addr, SAS_ADDR_SIZE);
	return 0;
}