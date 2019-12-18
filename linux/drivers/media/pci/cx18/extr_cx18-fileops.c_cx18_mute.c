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
typedef  scalar_t__ u32 ;
struct cx18 {int /*<<< orphan*/  ana_capturing; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CPU_SET_AUDIO_MUTE ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_ERR (char*) ; 
 scalar_t__ CX18_INVALID_TASK_HANDLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cx18_find_handle (struct cx18*) ; 
 int /*<<< orphan*/  cx18_vapi (struct cx18*,int /*<<< orphan*/ ,int,scalar_t__,int) ; 

void cx18_mute(struct cx18 *cx)
{
	u32 h;
	if (atomic_read(&cx->ana_capturing)) {
		h = cx18_find_handle(cx);
		if (h != CX18_INVALID_TASK_HANDLE)
			cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2, h, 1);
		else
			CX18_ERR("Can't find valid task handle for mute\n");
	}
	CX18_DEBUG_INFO("Mute\n");
}