#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct file {struct aspeed_p2a_user* private_data; } ;
struct aspeed_p2a_user {scalar_t__ read; scalar_t__* readwrite; TYPE_3__* parent; } ;
struct TYPE_6__ {scalar_t__ readers; scalar_t__* readerwriters; int /*<<< orphan*/  tracking; int /*<<< orphan*/  regmap; TYPE_2__* config; } ;
struct TYPE_5__ {TYPE_1__* regions; } ;
struct TYPE_4__ {int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int P2A_REGION_COUNT ; 
 int /*<<< orphan*/  SCU2C ; 
 int /*<<< orphan*/  aspeed_p2a_disable_bridge (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct aspeed_p2a_user*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_p2a_release(struct inode *inode, struct file *file)
{
	int i;
	u32 bits = 0;
	bool open_regions = false;
	struct aspeed_p2a_user *priv = file->private_data;

	/* Lock others from changing these values until everything is updated
	 * in one pass.
	 */
	mutex_lock(&priv->parent->tracking);

	priv->parent->readers -= priv->read;

	for (i = 0; i < P2A_REGION_COUNT; i++) {
		priv->parent->readerwriters[i] -= priv->readwrite[i];

		if (priv->parent->readerwriters[i] > 0)
			open_regions = true;
		else
			bits |= priv->parent->config->regions[i].bit;
	}

	/* Setting a bit to 1 disables the region, so let's just OR with the
	 * above to disable any.
	 */

	/* Note, if another user is trying to ioctl, they can't grab tracking,
	 * and therefore can't grab either register mutex.
	 * If another user is trying to close, they can't grab tracking either.
	 */
	regmap_update_bits(priv->parent->regmap, SCU2C, bits, bits);

	/* If parent->readers is zero and open windows is 0, disable the
	 * bridge.
	 */
	if (!open_regions && priv->parent->readers == 0)
		aspeed_p2a_disable_bridge(priv->parent);

	mutex_unlock(&priv->parent->tracking);

	kfree(priv);

	return 0;
}