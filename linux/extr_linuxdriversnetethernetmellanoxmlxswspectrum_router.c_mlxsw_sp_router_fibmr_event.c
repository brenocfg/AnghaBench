#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  mfc; } ;
struct mlxsw_sp_fib_event_work {int event; TYPE_1__ ven_info; TYPE_1__ men_info; } ;
struct fib_notifier_info {int dummy; } ;

/* Variables and functions */
#define  FIB_EVENT_ENTRY_ADD 132 
#define  FIB_EVENT_ENTRY_DEL 131 
#define  FIB_EVENT_ENTRY_REPLACE 130 
#define  FIB_EVENT_VIF_ADD 129 
#define  FIB_EVENT_VIF_DEL 128 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct fib_notifier_info*,int) ; 
 int /*<<< orphan*/  mr_cache_hold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_router_fibmr_event(struct mlxsw_sp_fib_event_work *fib_work,
			    struct fib_notifier_info *info)
{
	switch (fib_work->event) {
	case FIB_EVENT_ENTRY_REPLACE: /* fall through */
	case FIB_EVENT_ENTRY_ADD: /* fall through */
	case FIB_EVENT_ENTRY_DEL:
		memcpy(&fib_work->men_info, info, sizeof(fib_work->men_info));
		mr_cache_hold(fib_work->men_info.mfc);
		break;
	case FIB_EVENT_VIF_ADD: /* fall through */
	case FIB_EVENT_VIF_DEL:
		memcpy(&fib_work->ven_info, info, sizeof(fib_work->ven_info));
		dev_hold(fib_work->ven_info.dev);
		break;
	}
}