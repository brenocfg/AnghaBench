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
typedef  int u32 ;
struct realtek_pci_sdmmc {int dummy; } ;

/* Variables and functions */
 int RTSX_PHASE_MAX ; 
 int sd_tuning_rx_cmd (struct realtek_pci_sdmmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_tuning_phase(struct realtek_pci_sdmmc *host,
		u8 opcode, u32 *phase_map)
{
	int err, i;
	u32 raw_phase_map = 0;

	for (i = 0; i < RTSX_PHASE_MAX; i++) {
		err = sd_tuning_rx_cmd(host, opcode, (u8)i);
		if (err == 0)
			raw_phase_map |= 1 << i;
	}

	if (phase_map)
		*phase_map = raw_phase_map;

	return 0;
}