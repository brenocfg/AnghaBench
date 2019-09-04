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
typedef  unsigned char u8 ;

/* Variables and functions */
 int HFI1_VNIC_MAX_PAD ; 
 unsigned char OPA_VNIC_ICRC_TAIL_LEN ; 

__attribute__((used)) static inline void hfi1_vnic_update_pad(unsigned char *pad, u8 plen)
{
	pad[HFI1_VNIC_MAX_PAD - 1] = plen - OPA_VNIC_ICRC_TAIL_LEN;
}