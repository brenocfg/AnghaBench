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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_HTC_SVC_ID_HTT_LOG_MSG ; 
 int ath10k_hif_map_service_to_pipe (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath10k_htc_pktlog_svc_supported(struct ath10k *ar)
{
	u8 ul_pipe_id;
	u8 dl_pipe_id;
	int status;

	status = ath10k_hif_map_service_to_pipe(ar, ATH10K_HTC_SVC_ID_HTT_LOG_MSG,
						&ul_pipe_id,
						&dl_pipe_id);
	if (status) {
		ath10k_warn(ar, "unsupported HTC service id: %d\n",
			    ATH10K_HTC_SVC_ID_HTT_LOG_MSG);

		return false;
	}

	return true;
}