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
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int ath6kl_fetch_fw_file (struct ath6kl*) ; 
 int ath6kl_fetch_otp_file (struct ath6kl*) ; 
 int ath6kl_fetch_patch_file (struct ath6kl*) ; 
 int ath6kl_fetch_testscript_file (struct ath6kl*) ; 

__attribute__((used)) static int ath6kl_fetch_fw_api1(struct ath6kl *ar)
{
	int ret;

	ret = ath6kl_fetch_otp_file(ar);
	if (ret)
		return ret;

	ret = ath6kl_fetch_fw_file(ar);
	if (ret)
		return ret;

	ret = ath6kl_fetch_patch_file(ar);
	if (ret)
		return ret;

	ret = ath6kl_fetch_testscript_file(ar);
	if (ret)
		return ret;

	return 0;
}