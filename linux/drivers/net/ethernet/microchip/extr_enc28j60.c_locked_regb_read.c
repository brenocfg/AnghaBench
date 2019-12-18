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
typedef  int /*<<< orphan*/  u8 ;
struct enc28j60_net {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nolock_regb_read (struct enc28j60_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int locked_regb_read(struct enc28j60_net *priv, u8 address)
{
	int ret;

	mutex_lock(&priv->lock);
	ret = nolock_regb_read(priv, address);
	mutex_unlock(&priv->lock);

	return ret;
}