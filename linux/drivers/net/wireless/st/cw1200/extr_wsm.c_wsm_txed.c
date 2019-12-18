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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ptr; } ;
struct cw1200_common {TYPE_1__ wsm_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void wsm_txed(struct cw1200_common *priv, u8 *data)
{
	if (data == priv->wsm_cmd.ptr) {
		spin_lock(&priv->wsm_cmd.lock);
		priv->wsm_cmd.ptr = NULL;
		spin_unlock(&priv->wsm_cmd.lock);
	}
}