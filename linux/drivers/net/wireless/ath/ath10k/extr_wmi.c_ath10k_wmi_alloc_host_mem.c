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
typedef  scalar_t__ u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ath10k_wmi_alloc_chunk (struct ath10k*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ath10k_wmi_alloc_host_mem(struct ath10k *ar, u32 req_id,
				     u32 num_units, u32 unit_len)
{
	int ret;

	while (num_units) {
		ret = ath10k_wmi_alloc_chunk(ar, req_id, num_units, unit_len);
		if (ret < 0)
			return ret;

		num_units -= ret;
	}

	return 0;
}