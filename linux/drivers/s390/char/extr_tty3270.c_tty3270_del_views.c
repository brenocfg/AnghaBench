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
struct raw3270_view {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct raw3270_view*) ; 
 int RAW3270_FIRSTMINOR ; 
 int /*<<< orphan*/  raw3270_del_view (struct raw3270_view*) ; 
 struct raw3270_view* raw3270_find_view (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty3270_fn ; 
 int tty3270_max_index ; 

__attribute__((used)) static void
tty3270_del_views(void)
{
	int i;

	for (i = RAW3270_FIRSTMINOR; i <= tty3270_max_index; i++) {
		struct raw3270_view *view = raw3270_find_view(&tty3270_fn, i);
		if (!IS_ERR(view))
			raw3270_del_view(view);
	}
}