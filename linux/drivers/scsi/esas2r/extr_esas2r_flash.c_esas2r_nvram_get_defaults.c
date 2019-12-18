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
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_sas_nvram {int /*<<< orphan*/ * sas_addr; } ;
struct esas2r_adapter {TYPE_1__* nvram; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sas_addr; } ;

/* Variables and functions */
 struct esas2r_sas_nvram default_sas_nvram ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void esas2r_nvram_get_defaults(struct esas2r_adapter *a,
			       struct esas2r_sas_nvram *nvram)
{
	u8 sas_addr[8];

	/*
	 * in case we are copying the defaults into the adapter, copy the SAS
	 * address out first.
	 */
	memcpy(&sas_addr[0], a->nvram->sas_addr, 8);
	*nvram = default_sas_nvram;
	memcpy(&nvram->sas_addr[0], &sas_addr[0], 8);
}