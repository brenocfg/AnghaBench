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
typedef  int /*<<< orphan*/  u32 ;
struct iproc_msi {int nr_msi_region; } ;

/* Variables and functions */
 unsigned int MSI_MEM_REGION_SIZE ; 
 int hwirq_to_group (struct iproc_msi*,unsigned long) ; 

__attribute__((used)) static inline unsigned int iproc_msi_addr_offset(struct iproc_msi *msi,
						 unsigned long hwirq)
{
	if (msi->nr_msi_region > 1)
		return hwirq_to_group(msi, hwirq) * MSI_MEM_REGION_SIZE;
	else
		return hwirq_to_group(msi, hwirq) * sizeof(u32);
}