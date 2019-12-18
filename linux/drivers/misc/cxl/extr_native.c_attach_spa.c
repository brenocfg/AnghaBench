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
typedef  int u64 ;
struct cxl_afu {TYPE_1__* native; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {int spa_max_procs; int spa_size; int /*<<< orphan*/ * sw_command_status; scalar_t__ spa; } ;

/* Variables and functions */
 int CXL_PSL_SPAP_Addr ; 
 int /*<<< orphan*/  CXL_PSL_SPAP_An ; 
 int CXL_PSL_SPAP_Size ; 
 int CXL_PSL_SPAP_Size_Shift ; 
 int CXL_PSL_SPAP_V ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_devel (char*,scalar_t__,int,int /*<<< orphan*/ *,int) ; 
 int virt_to_phys (scalar_t__) ; 

__attribute__((used)) static void attach_spa(struct cxl_afu *afu)
{
	u64 spap;

	afu->native->sw_command_status = (__be64 *)((char *)afu->native->spa +
					    ((afu->native->spa_max_procs + 3) * 128));

	spap = virt_to_phys(afu->native->spa) & CXL_PSL_SPAP_Addr;
	spap |= ((afu->native->spa_size >> (12 - CXL_PSL_SPAP_Size_Shift)) - 1) & CXL_PSL_SPAP_Size;
	spap |= CXL_PSL_SPAP_V;
	pr_devel("cxl: SPA allocated at 0x%p. Max processes: %i, sw_command_status: 0x%p CXL_PSL_SPAP_An=0x%016llx\n",
		afu->native->spa, afu->native->spa_max_procs,
		afu->native->sw_command_status, spap);
	cxl_p1n_write(afu, CXL_PSL_SPAP_An, spap);
}