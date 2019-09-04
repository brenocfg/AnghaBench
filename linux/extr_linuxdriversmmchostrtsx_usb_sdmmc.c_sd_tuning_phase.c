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
typedef  int u16 ;
struct rtsx_usb_sdmmc {int dummy; } ;

/* Variables and functions */
 int MAX_PHASE ; 
 int sd_tuning_rx_cmd (struct rtsx_usb_sdmmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_tuning_phase(struct rtsx_usb_sdmmc *host,
		u8 opcode, u16 *phase_map)
{
	int err, i;
	u16 raw_phase_map = 0;

	for (i = MAX_PHASE; i >= 0; i--) {
		err = sd_tuning_rx_cmd(host, opcode, (u8)i);
		if (!err)
			raw_phase_map |= 1 << i;
	}

	if (phase_map)
		*phase_map = raw_phase_map;
}