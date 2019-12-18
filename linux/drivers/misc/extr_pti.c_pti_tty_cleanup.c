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
struct tty_struct {struct pti_tty* driver_data; } ;
struct pti_tty {int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pti_tty*) ; 
 int /*<<< orphan*/  pti_release_masterchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pti_tty_cleanup(struct tty_struct *tty)
{
	struct pti_tty *pti_tty_data = tty->driver_data;
	if (pti_tty_data == NULL)
		return;
	pti_release_masterchannel(pti_tty_data->mc);
	kfree(pti_tty_data);
	tty->driver_data = NULL;
}