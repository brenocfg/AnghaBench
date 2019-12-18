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
 int CYBER9397 ; 
 int CYBER9397DVD ; 
 int CYBER9520 ; 
 int CYBER9525DVD ; 
 int IMAGE975 ; 
 int IMAGE985 ; 
 scalar_t__ is_blade (int) ; 
 scalar_t__ is_xp (int) ; 

__attribute__((used)) static inline int is3Dchip(int id)
{
	return	is_blade(id) || is_xp(id) ||
		(id == CYBER9397) || (id == CYBER9397DVD) ||
		(id == CYBER9520) || (id == CYBER9525DVD) ||
		(id == IMAGE975) || (id == IMAGE985);
}