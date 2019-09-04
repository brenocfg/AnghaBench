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
struct rbd_client {int /*<<< orphan*/  client; } ;
struct ceph_options {int dummy; } ;

/* Variables and functions */
 struct rbd_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  ceph_destroy_options (struct ceph_options*) ; 
 int /*<<< orphan*/  client_mutex ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rbd_client* rbd_client_create (struct ceph_options*) ; 
 struct rbd_client* rbd_client_find (struct ceph_options*) ; 
 int /*<<< orphan*/  rbd_put_client (struct rbd_client*) ; 
 int /*<<< orphan*/  rbd_warn (int /*<<< orphan*/ *,char*,int) ; 
 int wait_for_latest_osdmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rbd_client *rbd_get_client(struct ceph_options *ceph_opts)
{
	struct rbd_client *rbdc;
	int ret;

	mutex_lock_nested(&client_mutex, SINGLE_DEPTH_NESTING);
	rbdc = rbd_client_find(ceph_opts);
	if (rbdc) {
		ceph_destroy_options(ceph_opts);

		/*
		 * Using an existing client.  Make sure ->pg_pools is up to
		 * date before we look up the pool id in do_rbd_add().
		 */
		ret = wait_for_latest_osdmap(rbdc->client);
		if (ret) {
			rbd_warn(NULL, "failed to get latest osdmap: %d", ret);
			rbd_put_client(rbdc);
			rbdc = ERR_PTR(ret);
		}
	} else {
		rbdc = rbd_client_create(ceph_opts);
	}
	mutex_unlock(&client_mutex);

	return rbdc;
}