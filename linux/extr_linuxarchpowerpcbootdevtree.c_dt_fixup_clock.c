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
typedef  int u32 ;

/* Variables and functions */
 int MHZ (int) ; 
 void* finddevice (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,int) ; 
 int /*<<< orphan*/  setprop_val (void*,char*,int) ; 

void dt_fixup_clock(const char *path, u32 freq)
{
	void *devp = finddevice(path);

	if (devp) {
		printf("%s: clock-frequency <- %x (%dMHz)\n\r", path, freq, MHZ(freq));
		setprop_val(devp, "clock-frequency", freq);
	}
}