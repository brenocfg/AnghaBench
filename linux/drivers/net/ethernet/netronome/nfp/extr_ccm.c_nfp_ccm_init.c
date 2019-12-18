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
struct nfp_ccm {int /*<<< orphan*/  wq; int /*<<< orphan*/  replies; struct nfp_app* app; } ;
struct nfp_app {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

int nfp_ccm_init(struct nfp_ccm *ccm, struct nfp_app *app)
{
	ccm->app = app;
	skb_queue_head_init(&ccm->replies);
	init_waitqueue_head(&ccm->wq);
	return 0;
}