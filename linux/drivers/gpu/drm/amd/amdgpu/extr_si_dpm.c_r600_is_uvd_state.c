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
 int ATOM_PPLIB_CLASSIFICATION2_MVC ; 
 int ATOM_PPLIB_CLASSIFICATION_HD2STATE ; 
 int ATOM_PPLIB_CLASSIFICATION_HDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_SDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_UVDSTATE ; 

__attribute__((used)) static bool r600_is_uvd_state(u32 class, u32 class2)
{
	if (class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		return true;
	if (class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
		return true;
	if (class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
		return true;
	if (class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
		return true;
	if (class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
		return true;
	return false;
}