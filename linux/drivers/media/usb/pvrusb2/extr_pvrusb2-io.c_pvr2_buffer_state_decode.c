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
typedef  enum pvr2_buffer_state { ____Placeholder_pvr2_buffer_state } pvr2_buffer_state ;

/* Variables and functions */
#define  pvr2_buffer_state_idle 131 
#define  pvr2_buffer_state_none 130 
#define  pvr2_buffer_state_queued 129 
#define  pvr2_buffer_state_ready 128 

__attribute__((used)) static const char *pvr2_buffer_state_decode(enum pvr2_buffer_state st)
{
	switch (st) {
	case pvr2_buffer_state_none: return "none";
	case pvr2_buffer_state_idle: return "idle";
	case pvr2_buffer_state_queued: return "queued";
	case pvr2_buffer_state_ready: return "ready";
	}
	return "unknown";
}