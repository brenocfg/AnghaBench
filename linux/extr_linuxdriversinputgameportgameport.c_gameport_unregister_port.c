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
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gameport_destroy_port (struct gameport*) ; 
 int /*<<< orphan*/  gameport_disconnect_port (struct gameport*) ; 
 int /*<<< orphan*/  gameport_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gameport_unregister_port(struct gameport *gameport)
{
	mutex_lock(&gameport_mutex);
	gameport_disconnect_port(gameport);
	gameport_destroy_port(gameport);
	mutex_unlock(&gameport_mutex);
}