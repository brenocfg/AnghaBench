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
struct ipoib_path {int /*<<< orphan*/  neigh_list; int /*<<< orphan*/  queue; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  broadcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_path_rec (struct ipoib_dev_priv*,struct ipoib_path*,void*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 struct ipoib_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipoib_path *path_rec_create(struct net_device *dev, void *gid)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct ipoib_path *path;

	if (!priv->broadcast)
		return NULL;

	path = kzalloc(sizeof(*path), GFP_ATOMIC);
	if (!path)
		return NULL;

	skb_queue_head_init(&path->queue);

	INIT_LIST_HEAD(&path->neigh_list);

	init_path_rec(priv, path, gid);

	return path;
}