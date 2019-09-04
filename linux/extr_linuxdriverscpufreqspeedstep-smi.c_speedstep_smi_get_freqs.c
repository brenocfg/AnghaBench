#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int event; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int GET_SPEEDSTEP_FREQS ; 
 TYPE_1__ ist_info ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int smi_cmd ; 
 int /*<<< orphan*/  smi_port ; 
 int smi_sig ; 

__attribute__((used)) static int speedstep_smi_get_freqs(unsigned int *low, unsigned int *high)
{
	u32 command, result = 0, edi, high_mhz, low_mhz, dummy;
	u32 state = 0;
	u32 function = GET_SPEEDSTEP_FREQS;

	if (!(ist_info.event & 0xFFFF)) {
		pr_debug("bug #1422 -- can't read freqs from BIOS\n");
		return -ENODEV;
	}

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);

	pr_debug("trying to determine frequencies with command %x at port %x\n",
			command, smi_port);

	__asm__ __volatile__(
		"push %%ebp\n"
		"out %%al, (%%dx)\n"
		"pop %%ebp"
		: "=a" (result),
		  "=b" (high_mhz),
		  "=c" (low_mhz),
		  "=d" (state), "=D" (edi), "=S" (dummy)
		: "a" (command),
		  "b" (function),
		  "c" (state),
		  "d" (smi_port), "S" (0), "D" (0)
	);

	pr_debug("result %x, low_freq %u, high_freq %u\n",
			result, low_mhz, high_mhz);

	/* abort if results are obviously incorrect... */
	if ((high_mhz + low_mhz) < 600)
		return -EINVAL;

	*high = high_mhz * 1000;
	*low  = low_mhz  * 1000;

	return result;
}