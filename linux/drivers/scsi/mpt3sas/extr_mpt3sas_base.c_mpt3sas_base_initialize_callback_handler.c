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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ MPT_MAX_CALLBACKS ; 
 int /*<<< orphan*/  mpt3sas_base_release_callback_handler (scalar_t__) ; 

void
mpt3sas_base_initialize_callback_handler(void)
{
	u8 cb_idx;

	for (cb_idx = 0; cb_idx < MPT_MAX_CALLBACKS; cb_idx++)
		mpt3sas_base_release_callback_handler(cb_idx);
}