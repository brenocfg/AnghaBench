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
struct sh_pfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8a7794_tdsel ; 
 int /*<<< orphan*/  sh_pfc_write (struct sh_pfc*,int,int) ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r8a7794_pinmux_soc_init(struct sh_pfc *pfc)
{
	/* Initialize TDSEL on old revisions */
	if (soc_device_match(r8a7794_tdsel))
		sh_pfc_write(pfc, 0xe6060068, 0x55555500);

	return 0;
}