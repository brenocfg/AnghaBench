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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {int media; int /*<<< orphan*/  timer; scalar_t__ tcount; int /*<<< orphan*/  c_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO ; 
 int /*<<< orphan*/  DE4X5_MFC ; 
 int INIT ; 
 int /*<<< orphan*/  de4x5_ast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_ast (struct net_device*) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
autoconf_media(struct net_device *dev)
{
	struct de4x5_private *lp = netdev_priv(dev);
	u_long iobase = dev->base_addr;

	disable_ast(dev);

	lp->c_media = AUTO;                     /* Bogus last media */
	inl(DE4X5_MFC);                         /* Zero the lost frames counter */
	lp->media = INIT;
	lp->tcount = 0;

	de4x5_ast(&lp->timer);

	return lp->media;
}