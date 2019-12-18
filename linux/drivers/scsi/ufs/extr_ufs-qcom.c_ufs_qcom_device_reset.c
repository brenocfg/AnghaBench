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
struct ufs_qcom_host {int /*<<< orphan*/  device_reset; } ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct ufs_qcom_host* ufshcd_get_variant (struct ufs_hba*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ufs_qcom_device_reset(struct ufs_hba *hba)
{
	struct ufs_qcom_host *host = ufshcd_get_variant(hba);

	/* reset gpio is optional */
	if (!host->device_reset)
		return;

	/*
	 * The UFS device shall detect reset pulses of 1us, sleep for 10us to
	 * be on the safe side.
	 */
	gpiod_set_value_cansleep(host->device_reset, 1);
	usleep_range(10, 15);

	gpiod_set_value_cansleep(host->device_reset, 0);
	usleep_range(10, 15);
}