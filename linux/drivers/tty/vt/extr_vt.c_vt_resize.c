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
struct winsize {int /*<<< orphan*/  ws_row; int /*<<< orphan*/  ws_col; } ;
struct vc_data {int dummy; } ;
struct tty_struct {struct vc_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int vc_do_resize (struct tty_struct*,struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vt_resize(struct tty_struct *tty, struct winsize *ws)
{
	struct vc_data *vc = tty->driver_data;
	int ret;

	console_lock();
	ret = vc_do_resize(tty, vc, ws->ws_col, ws->ws_row);
	console_unlock();
	return ret;
}