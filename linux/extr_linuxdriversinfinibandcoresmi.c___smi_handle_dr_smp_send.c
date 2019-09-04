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
typedef  size_t u8 ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 int IB_SMI_DISCARD ; 
 int IB_SMI_HANDLE ; 
 size_t IB_SMP_MAX_PATH_HOPS ; 

__attribute__((used)) static enum smi_action __smi_handle_dr_smp_send(bool is_switch, int port_num,
						u8 *hop_ptr, u8 hop_cnt,
						const u8 *initial_path,
						const u8 *return_path,
						u8 direction,
						bool dr_dlid_is_permissive,
						bool dr_slid_is_permissive)
{
	/* See section 14.2.2.2, Vol 1 IB spec */
	/* C14-6 -- valid hop_cnt values are from 0 to 63 */
	if (hop_cnt >= IB_SMP_MAX_PATH_HOPS)
		return IB_SMI_DISCARD;

	if (!direction) {
		/* C14-9:1 */
		if (hop_cnt && *hop_ptr == 0) {
			(*hop_ptr)++;
			return (initial_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-9:2 */
		if (*hop_ptr && *hop_ptr < hop_cnt) {
			if (!is_switch)
				return IB_SMI_DISCARD;

			/* return_path set when received */
			(*hop_ptr)++;
			return (initial_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-9:3 -- We're at the end of the DR segment of path */
		if (*hop_ptr == hop_cnt) {
			/* return_path set when received */
			(*hop_ptr)++;
			return (is_switch ||
				dr_dlid_is_permissive ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-9:4 -- hop_ptr = hop_cnt + 1 -> give to SMA/SM */
		/* C14-9:5 -- Fail unreasonable hop pointer */
		return (*hop_ptr == hop_cnt + 1 ? IB_SMI_HANDLE : IB_SMI_DISCARD);

	} else {
		/* C14-13:1 */
		if (hop_cnt && *hop_ptr == hop_cnt + 1) {
			(*hop_ptr)--;
			return (return_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-13:2 */
		if (2 <= *hop_ptr && *hop_ptr <= hop_cnt) {
			if (!is_switch)
				return IB_SMI_DISCARD;

			(*hop_ptr)--;
			return (return_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-13:3 -- at the end of the DR segment of path */
		if (*hop_ptr == 1) {
			(*hop_ptr)--;
			/* C14-13:3 -- SMPs destined for SM shouldn't be here */
			return (is_switch ||
				dr_slid_is_permissive ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-13:4 -- hop_ptr = 0 -> should have gone to SM */
		if (*hop_ptr == 0)
			return IB_SMI_HANDLE;

		/* C14-13:5 -- Check for unreasonable hop pointer */
		return IB_SMI_DISCARD;
	}
}