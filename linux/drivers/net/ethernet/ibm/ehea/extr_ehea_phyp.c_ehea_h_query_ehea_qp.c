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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  H_QUERY_HEA_QP ; 
 int /*<<< orphan*/  __pa (void*) ; 
 int /*<<< orphan*/  ehea_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_query_ehea_qp(const u64 adapter_handle, const u8 qp_category,
			 const u64 qp_handle, const u64 sel_mask, void *cb_addr)
{
	return ehea_plpar_hcall_norets(H_QUERY_HEA_QP,
				       adapter_handle,		/* R4 */
				       qp_category,		/* R5 */
				       qp_handle,		/* R6 */
				       sel_mask,		/* R7 */
				       __pa(cb_addr),		/* R8 */
				       0, 0);
}