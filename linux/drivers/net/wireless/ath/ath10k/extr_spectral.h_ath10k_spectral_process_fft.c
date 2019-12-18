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
struct wmi_phyerr_ev_arg {int dummy; } ;
struct phyerr_fft_report {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
ath10k_spectral_process_fft(struct ath10k *ar,
			    struct wmi_phyerr_ev_arg *phyerr,
			    const struct phyerr_fft_report *fftr,
			    size_t bin_len, u64 tsf)
{
	return 0;
}