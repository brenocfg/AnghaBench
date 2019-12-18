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
typedef  int u16 ;
struct vc_data {unsigned long vc_pos; } ;

/* Variables and functions */
 int scr_readw (int const*) ; 
 int softcursor_original ; 

u16 vcs_scr_readw(struct vc_data *vc, const u16 *org)
{
	if ((unsigned long)org == vc->vc_pos && softcursor_original != -1)
		return softcursor_original;
	return scr_readw(org);
}