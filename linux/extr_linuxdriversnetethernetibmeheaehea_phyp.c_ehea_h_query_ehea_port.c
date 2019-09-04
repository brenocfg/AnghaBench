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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EHEA_BMASK_SET (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  H_MEHEAPORT_CAT ; 
 int /*<<< orphan*/  H_MEHEAPORT_PN ; 
 int /*<<< orphan*/  H_QUERY_HEA_PORT ; 
 int __pa (void*) ; 
 int ehea_plpar_hcall_norets (int /*<<< orphan*/ ,int const,int,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_query_ehea_port(const u64 adapter_handle, const u16 port_num,
			   const u8 cb_cat, const u64 select_mask,
			   void *cb_addr)
{
	u64 port_info;
	u64 cb_logaddr = __pa(cb_addr);
	u64 arr_index = 0;

	port_info = EHEA_BMASK_SET(H_MEHEAPORT_CAT, cb_cat)
		  | EHEA_BMASK_SET(H_MEHEAPORT_PN, port_num);

	return ehea_plpar_hcall_norets(H_QUERY_HEA_PORT,
				       adapter_handle,		/* R4 */
				       port_info,		/* R5 */
				       select_mask,		/* R6 */
				       arr_index,		/* R7 */
				       cb_logaddr,		/* R8 */
				       0, 0);			/* R9-R10 */
}