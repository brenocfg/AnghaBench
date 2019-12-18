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

/* Variables and functions */
 int DO01_ACTIVE_MODE ; 
 int DO0_ACTIVE_MODE ; 
 int DO1_ACTIVE_MODE ; 
 int INACTIVE_MODE ; 
#define  KOMEDA_MODE_DISP0 131 
#define  KOMEDA_MODE_DISP1 130 
#define  KOMEDA_MODE_DUAL_DISP 129 
#define  KOMEDA_MODE_INACTIVE 128 
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static int to_d71_opmode(int core_mode)
{
	switch (core_mode) {
	case KOMEDA_MODE_DISP0:
		return DO0_ACTIVE_MODE;
	case KOMEDA_MODE_DISP1:
		return DO1_ACTIVE_MODE;
	case KOMEDA_MODE_DUAL_DISP:
		return DO01_ACTIVE_MODE;
	case KOMEDA_MODE_INACTIVE:
		return INACTIVE_MODE;
	default:
		WARN(1, "Unknown operation mode");
		return INACTIVE_MODE;
	}
}