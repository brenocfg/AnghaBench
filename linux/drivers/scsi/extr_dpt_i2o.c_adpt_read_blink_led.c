#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ FwDebugBLEDvalue_P; scalar_t__ FwDebugBLEDflag_P; } ;
typedef  TYPE_1__ adpt_hba ;

/* Variables and functions */
 int readb (scalar_t__) ; 

__attribute__((used)) static u8 adpt_read_blink_led(adpt_hba* host)
{
	if (host->FwDebugBLEDflag_P) {
		if( readb(host->FwDebugBLEDflag_P) == 0xbc ){
			return readb(host->FwDebugBLEDvalue_P);
		}
	}
	return 0;
}