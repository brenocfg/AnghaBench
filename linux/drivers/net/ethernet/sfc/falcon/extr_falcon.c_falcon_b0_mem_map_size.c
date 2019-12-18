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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 unsigned int FR_BZ_RX_INDIRECTION_TBL ; 
 int FR_BZ_RX_INDIRECTION_TBL_ROWS ; 
 int FR_BZ_RX_INDIRECTION_TBL_STEP ; 

__attribute__((used)) static unsigned int falcon_b0_mem_map_size(struct ef4_nic *efx)
{
	/* Map everything up to and including the RSS indirection table.
	 * The PCI core takes care of mapping the MSI-X tables.
	 */
	return FR_BZ_RX_INDIRECTION_TBL +
		FR_BZ_RX_INDIRECTION_TBL_STEP * FR_BZ_RX_INDIRECTION_TBL_ROWS;
}