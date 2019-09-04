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
 int /*<<< orphan*/  __zpci_event_error (void*) ; 
 scalar_t__ zpci_is_enabled () ; 

void zpci_event_error(void *data)
{
	if (zpci_is_enabled())
		__zpci_event_error(data);
}