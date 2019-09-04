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
 int STATUS_DIR ; 
 int STATUS_DMA ; 
 int STATUS_READY ; 

__attribute__((used)) static bool is_ready_state(int status)
{
	int state = status & (STATUS_READY | STATUS_DIR | STATUS_DMA);
	return state == STATUS_READY;
}