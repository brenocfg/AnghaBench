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
 int LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NI_STATUS_REV_ID ; 
 int NSRI_REGIONSIZE_MASK ; 
 int NSRI_REGIONSIZE_SHFT ; 
 int REGIONSIZE_FINE ; 

__attribute__((used)) static int is_fine_dirmode(void)
{
	return ((LOCAL_HUB_L(NI_STATUS_REV_ID) & NSRI_REGIONSIZE_MASK) >> NSRI_REGIONSIZE_SHFT) & REGIONSIZE_FINE;
}