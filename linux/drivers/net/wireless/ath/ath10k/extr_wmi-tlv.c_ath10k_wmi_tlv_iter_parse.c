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
typedef  size_t u16 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 size_t WMI_TLV_TAG_MAX ; 

__attribute__((used)) static int ath10k_wmi_tlv_iter_parse(struct ath10k *ar, u16 tag, u16 len,
				     const void *ptr, void *data)
{
	const void **tb = data;

	if (tag < WMI_TLV_TAG_MAX)
		tb[tag] = ptr;

	return 0;
}