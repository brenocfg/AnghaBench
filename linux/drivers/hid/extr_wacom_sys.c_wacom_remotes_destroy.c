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
struct wacom_remote {int /*<<< orphan*/  remote_fifo; int /*<<< orphan*/  remote_dir; } ;
struct wacom {struct wacom_remote* remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_remotes_destroy(void *data)
{
	struct wacom *wacom = data;
	struct wacom_remote *remote = wacom->remote;

	if (!remote)
		return;

	kobject_put(remote->remote_dir);
	kfifo_free(&remote->remote_fifo);
	wacom->remote = NULL;
}