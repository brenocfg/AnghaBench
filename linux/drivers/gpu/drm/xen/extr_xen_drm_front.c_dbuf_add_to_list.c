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
typedef  int /*<<< orphan*/  u64 ;
struct xen_drm_front_info {int /*<<< orphan*/  dbuf_list; } ;
struct xen_drm_front_dbuf {int /*<<< orphan*/  list; int /*<<< orphan*/  dbuf_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dbuf_add_to_list(struct xen_drm_front_info *front_info,
			     struct xen_drm_front_dbuf *dbuf, u64 dbuf_cookie)
{
	dbuf->dbuf_cookie = dbuf_cookie;
	list_add(&dbuf->list, &front_info->dbuf_list);
}