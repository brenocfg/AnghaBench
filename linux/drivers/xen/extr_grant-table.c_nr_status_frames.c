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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPP ; 
 unsigned int gnttab_frames (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gnttab_interface ; 

__attribute__((used)) static unsigned int nr_status_frames(unsigned int nr_grant_frames)
{
	BUG_ON(gnttab_interface == NULL);
	return gnttab_frames(nr_grant_frames, SPP);
}