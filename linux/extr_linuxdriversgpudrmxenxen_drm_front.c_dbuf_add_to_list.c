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
struct xen_drm_front_shbuf {int dummy; } ;
struct xen_drm_front_info {int /*<<< orphan*/  dbuf_list; } ;
struct xen_drm_front_dbuf {int /*<<< orphan*/  list; struct xen_drm_front_shbuf* shbuf; int /*<<< orphan*/  dbuf_cookie; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xen_drm_front_dbuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbuf_add_to_list(struct xen_drm_front_info *front_info,
			    struct xen_drm_front_shbuf *shbuf, u64 dbuf_cookie)
{
	struct xen_drm_front_dbuf *dbuf;

	dbuf = kzalloc(sizeof(*dbuf), GFP_KERNEL);
	if (!dbuf)
		return -ENOMEM;

	dbuf->dbuf_cookie = dbuf_cookie;
	dbuf->shbuf = shbuf;
	list_add(&dbuf->list, &front_info->dbuf_list);
	return 0;
}