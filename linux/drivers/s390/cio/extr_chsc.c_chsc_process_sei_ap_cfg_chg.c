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
struct chsc_sei_nt0_area {int rs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*) ; 
 int /*<<< orphan*/  ap_bus_cfg_chg () ; 

__attribute__((used)) static void chsc_process_sei_ap_cfg_chg(struct chsc_sei_nt0_area *sei_area)
{
	CIO_CRW_EVENT(3, "chsc: ap config changed\n");
	if (sei_area->rs != 5)
		return;

	ap_bus_cfg_chg();
}