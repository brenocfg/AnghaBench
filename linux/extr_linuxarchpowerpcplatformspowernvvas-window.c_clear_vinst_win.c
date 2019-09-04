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
struct vas_window {int winid; size_t cop; int /*<<< orphan*/  tx_win; int /*<<< orphan*/  user_win; struct vas_instance* vinst; } ;
struct vas_instance {int /*<<< orphan*/  mutex; struct vas_window** windows; int /*<<< orphan*/ ** rxwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_vinst_win(struct vas_window *window)
{
	int id = window->winid;
	struct vas_instance *vinst = window->vinst;

	mutex_lock(&vinst->mutex);

	if (!window->user_win && !window->tx_win) {
		WARN_ON_ONCE(!vinst->rxwin[window->cop]);
		vinst->rxwin[window->cop] = NULL;
	}

	WARN_ON_ONCE(vinst->windows[id] != window);
	vinst->windows[id] = NULL;

	mutex_unlock(&vinst->mutex);
}