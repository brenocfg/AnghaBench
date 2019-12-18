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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_3V3 ; 
 int /*<<< orphan*/  rts5260_stop_cmd (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5260_switch_output_voltage (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts5260_card_before_power_off(struct rtsx_pcr *pcr)
{
	rts5260_stop_cmd(pcr);
	rts5260_switch_output_voltage(pcr, OUTPUT_3V3);

}