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
struct wkup_m3_ipc {unsigned long resume_addr; } ;

/* Variables and functions */

__attribute__((used)) static void wkup_m3_set_resume_address(struct wkup_m3_ipc *m3_ipc, void *addr)
{
	m3_ipc->resume_addr = (unsigned long)addr;
}