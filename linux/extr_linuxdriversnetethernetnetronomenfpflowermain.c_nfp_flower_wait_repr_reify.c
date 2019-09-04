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
struct nfp_flower_priv {int /*<<< orphan*/  reify_wait_queue; } ;
struct nfp_app {int /*<<< orphan*/  cpp; TYPE_1__* pf; struct nfp_flower_priv* priv; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EIO ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_flower_wait_repr_reify(struct nfp_app *app, atomic_t *replies, int tot_repl)
{
	struct nfp_flower_priv *priv = app->priv;
	int err;

	if (!tot_repl)
		return 0;

	lockdep_assert_held(&app->pf->lock);
	err = wait_event_interruptible_timeout(priv->reify_wait_queue,
					       atomic_read(replies) >= tot_repl,
					       msecs_to_jiffies(10));
	if (err <= 0) {
		nfp_warn(app->cpp, "Not all reprs responded to reify\n");
		return -EIO;
	}

	return 0;
}