#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct iscsi_np {struct cxgbit_np* np_context; struct sockaddr_storage np_sockaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  completion; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * cdev; struct sockaddr_storage local_addr; TYPE_1__ wr_wait; } ;
struct cxgbit_np {TYPE_2__ com; struct iscsi_np* np; int /*<<< orphan*/  kref; int /*<<< orphan*/  np_accept_lock; int /*<<< orphan*/  np_accept_list; int /*<<< orphan*/  accept_comp; int /*<<< orphan*/  accept_wait; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CSK_STATE_LISTEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ cxgbit_inaddr_any (struct cxgbit_np*) ; 
 int /*<<< orphan*/  cxgbit_put_cnp (struct cxgbit_np*) ; 
 int cxgbit_setup_all_np (struct cxgbit_np*) ; 
 int cxgbit_setup_cdev_np (struct cxgbit_np*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct cxgbit_np* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int cxgbit_setup_np(struct iscsi_np *np, struct sockaddr_storage *ksockaddr)
{
	struct cxgbit_np *cnp;
	int ret;

	if ((ksockaddr->ss_family != AF_INET) &&
	    (ksockaddr->ss_family != AF_INET6))
		return -EINVAL;

	cnp = kzalloc(sizeof(*cnp), GFP_KERNEL);
	if (!cnp)
		return -ENOMEM;

	init_waitqueue_head(&cnp->accept_wait);
	init_completion(&cnp->com.wr_wait.completion);
	init_completion(&cnp->accept_comp);
	INIT_LIST_HEAD(&cnp->np_accept_list);
	spin_lock_init(&cnp->np_accept_lock);
	kref_init(&cnp->kref);
	memcpy(&np->np_sockaddr, ksockaddr,
	       sizeof(struct sockaddr_storage));
	memcpy(&cnp->com.local_addr, &np->np_sockaddr,
	       sizeof(cnp->com.local_addr));

	cnp->np = np;
	cnp->com.cdev = NULL;

	if (cxgbit_inaddr_any(cnp))
		ret = cxgbit_setup_all_np(cnp);
	else
		ret = cxgbit_setup_cdev_np(cnp);

	if (ret) {
		cxgbit_put_cnp(cnp);
		return -EINVAL;
	}

	np->np_context = cnp;
	cnp->com.state = CSK_STATE_LISTEN;
	return 0;
}