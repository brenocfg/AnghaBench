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
typedef  int u8 ;
struct list_head {int dummy; } ;
struct ipoib_mcast {int /*<<< orphan*/  list; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  flags; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  multicast_tree; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_SENDONLY ; 
 struct ipoib_mcast* __ipoib_mcast_find (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ipoib_check_and_add_mcast_sendonly(struct ipoib_dev_priv *priv, u8 *mgid,
				struct list_head *remove_list)
{
	/* Is this multicast ? */
	if (*mgid == 0xff) {
		struct ipoib_mcast *mcast = __ipoib_mcast_find(priv->dev, mgid);

		if (mcast && test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags)) {
			list_del(&mcast->list);
			rb_erase(&mcast->rb_node, &priv->multicast_tree);
			list_add_tail(&mcast->list, remove_list);
		}
	}
}