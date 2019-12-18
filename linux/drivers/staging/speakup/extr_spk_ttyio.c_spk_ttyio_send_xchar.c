#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* send_xchar ) (TYPE_2__*,char) ;} ;

/* Variables and functions */
 scalar_t__ check_tty (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* speakup_tty ; 
 int /*<<< orphan*/  speakup_tty_mutex ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char) ; 

__attribute__((used)) static void spk_ttyio_send_xchar(char ch)
{
	mutex_lock(&speakup_tty_mutex);
	if (check_tty(speakup_tty)) {
		mutex_unlock(&speakup_tty_mutex);
		return;
	}

	if (speakup_tty->ops->send_xchar)
		speakup_tty->ops->send_xchar(speakup_tty, ch);
	mutex_unlock(&speakup_tty_mutex);
}