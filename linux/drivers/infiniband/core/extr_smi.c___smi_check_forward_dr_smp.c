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
typedef  int u8 ;
typedef  enum smi_forward_action { ____Placeholder_smi_forward_action } smi_forward_action ;

/* Variables and functions */
 int IB_SMI_FORWARD ; 
 int IB_SMI_LOCAL ; 
 int IB_SMI_SEND ; 

__attribute__((used)) static enum smi_forward_action __smi_check_forward_dr_smp(u8 hop_ptr, u8 hop_cnt,
							  u8 direction,
							  bool dr_dlid_is_permissive,
							  bool dr_slid_is_permissive)
{
	if (!direction) {
		/* C14-9:2 -- intermediate hop */
		if (hop_ptr && hop_ptr < hop_cnt)
			return IB_SMI_FORWARD;

		/* C14-9:3 -- at the end of the DR segment of path */
		if (hop_ptr == hop_cnt)
			return (dr_dlid_is_permissive ?
				IB_SMI_SEND : IB_SMI_LOCAL);

		/* C14-9:4 -- hop_ptr = hop_cnt + 1 -> give to SMA/SM */
		if (hop_ptr == hop_cnt + 1)
			return IB_SMI_SEND;
	} else {
		/* C14-13:2  -- intermediate hop */
		if (2 <= hop_ptr && hop_ptr <= hop_cnt)
			return IB_SMI_FORWARD;

		/* C14-13:3 -- at the end of the DR segment of path */
		if (hop_ptr == 1)
			return (!dr_slid_is_permissive ?
				IB_SMI_SEND : IB_SMI_LOCAL);
	}
	return IB_SMI_LOCAL;

}