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
struct ath6kl {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_SUSPEND ; 
#define  ATH6KL_STATE_CUTPOWER 130 
#define  ATH6KL_STATE_DEEPSLEEP 129 
#define  ATH6KL_STATE_WOW 128 
 int ath6kl_cfg80211_deepsleep_resume (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int ath6kl_init_hw_start (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,int) ; 
 int ath6kl_wow_resume (struct ath6kl*) ; 

int ath6kl_cfg80211_resume(struct ath6kl *ar)
{
	int ret;

	switch (ar->state) {
	case  ATH6KL_STATE_WOW:
		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "wow mode resume\n");

		ret = ath6kl_wow_resume(ar);
		if (ret) {
			ath6kl_warn("wow mode resume failed: %d\n", ret);
			return ret;
		}

		break;

	case ATH6KL_STATE_DEEPSLEEP:
		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "deep sleep resume\n");

		ret = ath6kl_cfg80211_deepsleep_resume(ar);
		if (ret) {
			ath6kl_warn("deep sleep resume failed: %d\n", ret);
			return ret;
		}
		break;

	case ATH6KL_STATE_CUTPOWER:
		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "resume restoring power\n");

		ret = ath6kl_init_hw_start(ar);
		if (ret) {
			ath6kl_warn("Failed to boot hw in resume: %d\n", ret);
			return ret;
		}
		break;

	default:
		break;
	}

	return 0;
}