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
typedef  scalar_t__ u32 ;
struct realtek_pci_sdmmc {int dummy; } ;

/* Variables and functions */
 int RTSX_PHASE_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int sd_get_phase_len (scalar_t__,int) ; 
 int /*<<< orphan*/  sdmmc_dev (struct realtek_pci_sdmmc*) ; 

__attribute__((used)) static u8 sd_search_final_phase(struct realtek_pci_sdmmc *host, u32 phase_map)
{
	int start = 0, len = 0;
	int start_final = 0, len_final = 0;
	u8 final_phase = 0xFF;

	if (phase_map == 0) {
		dev_err(sdmmc_dev(host), "phase error: [map:%x]\n", phase_map);
		return final_phase;
	}

	while (start < RTSX_PHASE_MAX) {
		len = sd_get_phase_len(phase_map, start);
		if (len_final < len) {
			start_final = start;
			len_final = len;
		}
		start += len ? len : 1;
	}

	final_phase = (start_final + len_final / 2) % RTSX_PHASE_MAX;
	dev_dbg(sdmmc_dev(host), "phase: [map:%x] [maxlen:%d] [final:%d]\n",
		phase_map, len_final, final_phase);

	return final_phase;
}