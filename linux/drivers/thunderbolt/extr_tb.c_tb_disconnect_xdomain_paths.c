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
struct tb_xdomain {int /*<<< orphan*/  is_unplugged; } ;
struct tb {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tb_disconnect_xdomain_paths (struct tb*,struct tb_xdomain*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tb_disconnect_xdomain_paths(struct tb *tb, struct tb_xdomain *xd)
{
	if (!xd->is_unplugged) {
		mutex_lock(&tb->lock);
		__tb_disconnect_xdomain_paths(tb, xd);
		mutex_unlock(&tb->lock);
	}
	return 0;
}