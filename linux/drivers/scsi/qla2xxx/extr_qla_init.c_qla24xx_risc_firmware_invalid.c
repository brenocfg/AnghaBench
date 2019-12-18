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
typedef  int uint32_t ;

/* Variables and functions */

bool qla24xx_risc_firmware_invalid(uint32_t *dword)
{
	return
	    !(dword[4] | dword[5] | dword[6] | dword[7]) ||
	    !(~dword[4] | ~dword[5] | ~dword[6] | ~dword[7]);
}