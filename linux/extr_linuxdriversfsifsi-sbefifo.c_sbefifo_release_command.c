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
struct sbefifo_user {scalar_t__ pending_len; int /*<<< orphan*/ * pending_cmd; } ;

/* Variables and functions */
 scalar_t__ is_vmalloc_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sbefifo_release_command(struct sbefifo_user *user)
{
	if (is_vmalloc_addr(user->pending_cmd))
		vfree(user->pending_cmd);
	user->pending_cmd = NULL;
	user->pending_len = 0;
}