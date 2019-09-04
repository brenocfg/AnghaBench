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
struct umcast_data {int /*<<< orphan*/ * remote_addr; int /*<<< orphan*/ * listen_addr; scalar_t__ unicast; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void umcast_remove(void *data)
{
	struct umcast_data *pri = data;

	kfree(pri->listen_addr);
	if (pri->unicast)
		kfree(pri->remote_addr);
	pri->listen_addr = pri->remote_addr = NULL;
}