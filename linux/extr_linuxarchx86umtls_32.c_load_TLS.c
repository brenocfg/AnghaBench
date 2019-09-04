#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int entry_number; } ;
struct uml_tls_struct {int flushed; TYPE_3__ tls; int /*<<< orphan*/  present; } ;
struct TYPE_6__ {struct uml_tls_struct* tls_array; } ;
struct TYPE_7__ {TYPE_1__ arch; } ;
struct task_struct {TYPE_2__ thread; } ;

/* Variables and functions */
 int GDT_ENTRY_TLS_MAX ; 
 int GDT_ENTRY_TLS_MIN ; 
 int /*<<< orphan*/  LDT_empty (TYPE_3__*) ; 
 int O_FORCE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_user_desc (TYPE_3__*) ; 
 int do_set_thread_area (TYPE_3__*) ; 

__attribute__((used)) static int load_TLS(int flags, struct task_struct *to)
{
	int ret = 0;
	int idx;

	for (idx = GDT_ENTRY_TLS_MIN; idx < GDT_ENTRY_TLS_MAX; idx++) {
		struct uml_tls_struct* curr =
			&to->thread.arch.tls_array[idx - GDT_ENTRY_TLS_MIN];

		/*
		 * Actually, now if it wasn't flushed it gets cleared and
		 * flushed to the host, which will clear it.
		 */
		if (!curr->present) {
			if (!curr->flushed) {
				clear_user_desc(&curr->tls);
				curr->tls.entry_number = idx;
			} else {
				WARN_ON(!LDT_empty(&curr->tls));
				continue;
			}
		}

		if (!(flags & O_FORCE) && curr->flushed)
			continue;

		ret = do_set_thread_area(&curr->tls);
		if (ret)
			goto out;

		curr->flushed = 1;
	}
out:
	return ret;
}