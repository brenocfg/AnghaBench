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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ib_nl_request_timeout ; 
 int /*<<< orphan*/  ib_nl_sa_request_seq ; 
 int /*<<< orphan*/  ib_nl_timed_work ; 
 int /*<<< orphan*/  ib_nl_wq ; 
 int ib_register_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcast_cleanup () ; 
 int mcast_init () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  tid ; 

int ib_sa_init(void)
{
	int ret;

	get_random_bytes(&tid, sizeof tid);

	atomic_set(&ib_nl_sa_request_seq, 0);

	ret = ib_register_client(&sa_client);
	if (ret) {
		pr_err("Couldn't register ib_sa client\n");
		goto err1;
	}

	ret = mcast_init();
	if (ret) {
		pr_err("Couldn't initialize multicast handling\n");
		goto err2;
	}

	ib_nl_wq = alloc_ordered_workqueue("ib_nl_sa_wq", WQ_MEM_RECLAIM);
	if (!ib_nl_wq) {
		ret = -ENOMEM;
		goto err3;
	}

	INIT_DELAYED_WORK(&ib_nl_timed_work, ib_nl_request_timeout);

	return 0;

err3:
	mcast_cleanup();
err2:
	ib_unregister_client(&sa_client);
err1:
	return ret;
}