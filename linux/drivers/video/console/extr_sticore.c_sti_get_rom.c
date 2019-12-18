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
struct sti_struct {int dummy; } ;

/* Variables and functions */
 struct sti_struct* default_sti ; 
 unsigned int num_sti_roms ; 
 int /*<<< orphan*/  sti_init_roms () ; 
 struct sti_struct** sti_roms ; 
 int /*<<< orphan*/  sticore_initialized ; 

struct sti_struct * sti_get_rom(unsigned int index)
{
	if (!sticore_initialized)
		sti_init_roms();

	if (index == 0)
		return default_sti;

	if (index > num_sti_roms)
		return NULL;

	return sti_roms[index-1];
}