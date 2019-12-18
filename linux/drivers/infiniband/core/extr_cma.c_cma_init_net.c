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
struct net {int dummy; } ;
struct cma_pernet {int /*<<< orphan*/  ib_ps; int /*<<< orphan*/  ipoib_ps; int /*<<< orphan*/  udp_ps; int /*<<< orphan*/  tcp_ps; } ;

/* Variables and functions */
 struct cma_pernet* cma_pernet (struct net*) ; 
 int /*<<< orphan*/  xa_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_init_net(struct net *net)
{
	struct cma_pernet *pernet = cma_pernet(net);

	xa_init(&pernet->tcp_ps);
	xa_init(&pernet->udp_ps);
	xa_init(&pernet->ipoib_ps);
	xa_init(&pernet->ib_ps);

	return 0;
}