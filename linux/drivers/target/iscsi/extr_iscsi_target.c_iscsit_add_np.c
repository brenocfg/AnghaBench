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
struct sockaddr_storage {int dummy; } ;
struct iscsi_np {int np_network_transport; int np_exports; TYPE_1__* np_transport; int /*<<< orphan*/  np_sockaddr; int /*<<< orphan*/  np_list; int /*<<< orphan*/  np_thread_state; int /*<<< orphan*/  np_thread; int /*<<< orphan*/  np_login_timer; int /*<<< orphan*/  np_restart_comp; int /*<<< orphan*/  np_thread_lock; int /*<<< orphan*/  np_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iscsi_np* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISCSI_NP_THREAD_ACTIVE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPF_IP_NETWORK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_np_list ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_handle_login_thread_timeout ; 
 int /*<<< orphan*/  iscsi_target_login_thread ; 
 int iscsi_target_setup_login_socket (struct iscsi_np*,struct sockaddr_storage*) ; 
 struct iscsi_np* iscsit_get_np (struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  kfree (struct iscsi_np*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct iscsi_np*,char*) ; 
 struct iscsi_np* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  np_lock ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct iscsi_np *iscsit_add_np(
	struct sockaddr_storage *sockaddr,
	int network_transport)
{
	struct iscsi_np *np;
	int ret;

	mutex_lock(&np_lock);

	/*
	 * Locate the existing struct iscsi_np if already active..
	 */
	np = iscsit_get_np(sockaddr, network_transport);
	if (np) {
		mutex_unlock(&np_lock);
		return np;
	}

	np = kzalloc(sizeof(*np), GFP_KERNEL);
	if (!np) {
		mutex_unlock(&np_lock);
		return ERR_PTR(-ENOMEM);
	}

	np->np_flags |= NPF_IP_NETWORK;
	np->np_network_transport = network_transport;
	spin_lock_init(&np->np_thread_lock);
	init_completion(&np->np_restart_comp);
	INIT_LIST_HEAD(&np->np_list);

	timer_setup(&np->np_login_timer, iscsi_handle_login_thread_timeout, 0);

	ret = iscsi_target_setup_login_socket(np, sockaddr);
	if (ret != 0) {
		kfree(np);
		mutex_unlock(&np_lock);
		return ERR_PTR(ret);
	}

	np->np_thread = kthread_run(iscsi_target_login_thread, np, "iscsi_np");
	if (IS_ERR(np->np_thread)) {
		pr_err("Unable to create kthread: iscsi_np\n");
		ret = PTR_ERR(np->np_thread);
		kfree(np);
		mutex_unlock(&np_lock);
		return ERR_PTR(ret);
	}
	/*
	 * Increment the np_exports reference count now to prevent
	 * iscsit_del_np() below from being run while a new call to
	 * iscsi_tpg_add_network_portal() for a matching iscsi_np is
	 * active.  We don't need to hold np->np_thread_lock at this
	 * point because iscsi_np has not been added to g_np_list yet.
	 */
	np->np_exports = 1;
	np->np_thread_state = ISCSI_NP_THREAD_ACTIVE;

	list_add_tail(&np->np_list, &g_np_list);
	mutex_unlock(&np_lock);

	pr_debug("CORE[0] - Added Network Portal: %pISpc on %s\n",
		&np->np_sockaddr, np->np_transport->name);

	return np;
}