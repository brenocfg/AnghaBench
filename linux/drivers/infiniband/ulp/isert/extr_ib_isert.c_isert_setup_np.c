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
struct sockaddr_storage {int dummy; } ;
struct rdma_cm_id {int dummy; } ;
struct isert_np {struct rdma_cm_id* cm_id; struct iscsi_np* np; int /*<<< orphan*/  pending; int /*<<< orphan*/  accepted; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
struct iscsi_np {struct isert_np* np_context; int /*<<< orphan*/  np_sockaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct rdma_cm_id*) ; 
 int PTR_ERR (struct rdma_cm_id*) ; 
 struct rdma_cm_id* isert_setup_id (struct isert_np*) ; 
 int /*<<< orphan*/  kfree (struct isert_np*) ; 
 struct isert_np* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isert_setup_np(struct iscsi_np *np,
	       struct sockaddr_storage *ksockaddr)
{
	struct isert_np *isert_np;
	struct rdma_cm_id *isert_lid;
	int ret;

	isert_np = kzalloc(sizeof(struct isert_np), GFP_KERNEL);
	if (!isert_np)
		return -ENOMEM;

	sema_init(&isert_np->sem, 0);
	mutex_init(&isert_np->mutex);
	INIT_LIST_HEAD(&isert_np->accepted);
	INIT_LIST_HEAD(&isert_np->pending);
	isert_np->np = np;

	/*
	 * Setup the np->np_sockaddr from the passed sockaddr setup
	 * in iscsi_target_configfs.c code..
	 */
	memcpy(&np->np_sockaddr, ksockaddr,
	       sizeof(struct sockaddr_storage));

	isert_lid = isert_setup_id(isert_np);
	if (IS_ERR(isert_lid)) {
		ret = PTR_ERR(isert_lid);
		goto out;
	}

	isert_np->cm_id = isert_lid;
	np->np_context = isert_np;

	return 0;

out:
	kfree(isert_np);

	return ret;
}