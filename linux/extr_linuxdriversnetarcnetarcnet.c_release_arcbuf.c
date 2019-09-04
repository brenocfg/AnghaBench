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
struct net_device {int dummy; } ;
struct arcnet_local {int* buf_queue; int first_free_buf; int next_buf; } ;

/* Variables and functions */
 scalar_t__ BUGLVL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  arc_cont (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void release_arcbuf(struct net_device *dev, int bufnum)
{
	struct arcnet_local *lp = netdev_priv(dev);
	int i;

	lp->buf_queue[lp->first_free_buf++] = bufnum;
	lp->first_free_buf %= 5;

	if (BUGLVL(D_DURING)) {
		arc_printk(D_DURING, dev, "release_arcbuf: freed #%d; buffer queue is now: ",
			   bufnum);
		for (i = lp->next_buf; i != lp->first_free_buf; i = (i + 1) % 5)
			arc_cont(D_DURING, "#%d ", lp->buf_queue[i]);
		arc_cont(D_DURING, "\n");
	}
}