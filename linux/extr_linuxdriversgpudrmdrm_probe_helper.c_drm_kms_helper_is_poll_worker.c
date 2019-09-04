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
struct work_struct {scalar_t__ func; } ;

/* Variables and functions */
 struct work_struct* current_work () ; 
 scalar_t__ output_poll_execute ; 

bool drm_kms_helper_is_poll_worker(void)
{
	struct work_struct *work = current_work();

	return work && work->func == output_poll_execute;
}