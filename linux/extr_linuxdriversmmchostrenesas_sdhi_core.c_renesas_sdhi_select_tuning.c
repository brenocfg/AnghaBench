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
struct tmio_mmc_host {int tap_num; unsigned long tap_set; int /*<<< orphan*/  taps; } ;
struct renesas_sdhi {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long SH_MOBILE_SDHI_MAX_TAP ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_RVSCNTL ; 
 int SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_RVSREQ ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_TAPSET ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int sd_scc_read32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_scc_write32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int renesas_sdhi_select_tuning(struct tmio_mmc_host *host)
{
	struct renesas_sdhi *priv = host_to_priv(host);
	unsigned long tap_cnt;  /* counter of tuning success */
	unsigned long tap_start;/* start position of tuning success */
	unsigned long tap_end;  /* end position of tuning success */
	unsigned long ntap;     /* temporary counter of tuning success */
	unsigned long i;

	/* Clear SCC_RVSREQ */
	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ, 0);

	/*
	 * When tuning CMD19 is issued twice for each tap, merge the
	 * result requiring the tap to be good in both runs before
	 * considering it for tuning selection.
	 */
	for (i = 0; i < host->tap_num * 2; i++) {
		int offset = host->tap_num * (i < host->tap_num ? 1 : -1);

		if (!test_bit(i, host->taps))
			clear_bit(i + offset, host->taps);
	}

	/*
	 * Find the longest consecutive run of successful probes.  If that
	 * is more than SH_MOBILE_SDHI_MAX_TAP probes long then use the
	 * center index as the tap.
	 */
	tap_cnt = 0;
	ntap = 0;
	tap_start = 0;
	tap_end = 0;
	for (i = 0; i < host->tap_num * 2; i++) {
		if (test_bit(i, host->taps)) {
			ntap++;
		} else {
			if (ntap > tap_cnt) {
				tap_start = i - ntap;
				tap_end = i - 1;
				tap_cnt = ntap;
			}
			ntap = 0;
		}
	}

	if (ntap > tap_cnt) {
		tap_start = i - ntap;
		tap_end = i - 1;
		tap_cnt = ntap;
	}

	if (tap_cnt >= SH_MOBILE_SDHI_MAX_TAP)
		host->tap_set = (tap_start + tap_end) / 2 % host->tap_num;
	else
		return -EIO;

	/* Set SCC */
	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_TAPSET, host->tap_set);

	/* Enable auto re-tuning */
	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL,
		       SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN |
		       sd_scc_read32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL));

	return 0;
}