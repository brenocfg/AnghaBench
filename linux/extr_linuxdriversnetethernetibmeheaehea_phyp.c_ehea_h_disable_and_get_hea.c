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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  H_DISABLE_AND_GET_HEA ; 
 int /*<<< orphan*/  H_DISABLE_GET_EHEA_WQE_P ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  ehea_plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_disable_and_get_hea(const u64 adapter_handle, const u64 qp_handle)
{
	unsigned long outs[PLPAR_HCALL9_BUFSIZE];

	return ehea_plpar_hcall9(H_DISABLE_AND_GET_HEA,
				 outs,
				 adapter_handle,		/* R4 */
				 H_DISABLE_GET_EHEA_WQE_P,	/* R5 */
				 qp_handle,			/* R6 */
				 0, 0, 0, 0, 0, 0);		/* R7-R12 */
}