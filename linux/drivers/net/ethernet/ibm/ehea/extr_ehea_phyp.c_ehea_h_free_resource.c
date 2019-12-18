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
 int /*<<< orphan*/  H_FREE_RESOURCE ; 
 int /*<<< orphan*/  ehea_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 ehea_h_free_resource(const u64 adapter_handle, const u64 res_handle,
			 u64 force_bit)
{
	return ehea_plpar_hcall_norets(H_FREE_RESOURCE,
				       adapter_handle,	   /* R4 */
				       res_handle,	   /* R5 */
				       force_bit,
				       0, 0, 0, 0);	   /* R7-R10 */
}