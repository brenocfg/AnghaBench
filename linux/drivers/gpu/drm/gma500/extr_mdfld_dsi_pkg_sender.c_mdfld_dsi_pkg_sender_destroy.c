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
struct mdfld_dsi_pkg_sender {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mdfld_dsi_pkg_sender*) ; 
 int /*<<< orphan*/  kfree (struct mdfld_dsi_pkg_sender*) ; 

void mdfld_dsi_pkg_sender_destroy(struct mdfld_dsi_pkg_sender *sender)
{
	if (!sender || IS_ERR(sender))
		return;

	/*free*/
	kfree(sender);
}