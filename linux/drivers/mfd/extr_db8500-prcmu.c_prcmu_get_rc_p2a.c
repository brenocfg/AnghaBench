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
typedef  enum romcode_read { ____Placeholder_romcode_read } romcode_read ;

/* Variables and functions */
 scalar_t__ PRCM_ROMCODE_P2A ; 
 int readb (scalar_t__) ; 
 scalar_t__ tcdm_base ; 

enum romcode_read prcmu_get_rc_p2a(void)
{
	return readb(tcdm_base + PRCM_ROMCODE_P2A);
}