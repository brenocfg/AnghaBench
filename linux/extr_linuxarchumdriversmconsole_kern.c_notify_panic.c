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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCONSOLE_PANIC ; 
 int /*<<< orphan*/  mconsole_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * notify_socket ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int notify_panic(struct notifier_block *self, unsigned long unused1,
			void *ptr)
{
	char *message = ptr;

	if (notify_socket == NULL)
		return 0;

	mconsole_notify(notify_socket, MCONSOLE_PANIC, message,
			strlen(message) + 1);
	return 0;
}