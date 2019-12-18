#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xa_mark_t ;
struct xarray {int dummy; } ;
struct TYPE_5__ {unsigned long xa_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 void* XA_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_STATE (TYPE_1__,struct xarray*,unsigned long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ xa_is_zero (void*) ; 
 TYPE_1__ xas ; 
 void* xas_find_marked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xas_retry (TYPE_1__*,void*) ; 

__attribute__((used)) static void *xan_find_marked(struct xarray *xa, unsigned long *indexp,
			     xa_mark_t filter)
{
	XA_STATE(xas, xa, *indexp);
	void *entry;

	rcu_read_lock();
	do {
		entry = xas_find_marked(&xas, ULONG_MAX, filter);
		if (xa_is_zero(entry))
			break;
	} while (xas_retry(&xas, entry));
	rcu_read_unlock();

	if (entry) {
		*indexp = xas.xa_index;
		if (xa_is_zero(entry))
			return NULL;
		return entry;
	}
	return XA_ERROR(-ENOENT);
}