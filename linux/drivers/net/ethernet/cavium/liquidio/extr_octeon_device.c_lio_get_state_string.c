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
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 size_t OCT_DEV_STATES ; 
 size_t OCT_DEV_STATE_INVALID ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 char** oct_dev_state_str ; 

char *lio_get_state_string(atomic_t *state_ptr)
{
	s32 istate = (s32)atomic_read(state_ptr);

	if (istate > OCT_DEV_STATES || istate < 0)
		return oct_dev_state_str[OCT_DEV_STATE_INVALID];
	return oct_dev_state_str[istate];
}