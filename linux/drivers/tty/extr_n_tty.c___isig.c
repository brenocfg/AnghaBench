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
struct tty_struct {int dummy; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kill_pgrp (struct pid*,int,int) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 struct pid* tty_get_pgrp (struct tty_struct*) ; 

__attribute__((used)) static void __isig(int sig, struct tty_struct *tty)
{
	struct pid *tty_pgrp = tty_get_pgrp(tty);
	if (tty_pgrp) {
		kill_pgrp(tty_pgrp, sig, 1);
		put_pid(tty_pgrp);
	}
}