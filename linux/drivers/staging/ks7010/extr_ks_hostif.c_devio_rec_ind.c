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
struct ks_wlan_private {unsigned char** dev_data; unsigned int* dev_size; int /*<<< orphan*/  dev_read_lock; int /*<<< orphan*/  devread_wait; int /*<<< orphan*/  rec_count; int /*<<< orphan*/  event_count; int /*<<< orphan*/  is_device_open; } ;

/* Variables and functions */
 size_t DEVICE_STOCK_COUNT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void devio_rec_ind(struct ks_wlan_private *priv, unsigned char *p,
			  unsigned int size)
{
	if (!priv->is_device_open)
		return;

	spin_lock(&priv->dev_read_lock);
	priv->dev_data[atomic_read(&priv->rec_count)] = p;
	priv->dev_size[atomic_read(&priv->rec_count)] = size;

	if (atomic_read(&priv->event_count) != DEVICE_STOCK_COUNT) {
		/* rx event count inc */
		atomic_inc(&priv->event_count);
	}
	atomic_inc(&priv->rec_count);
	if (atomic_read(&priv->rec_count) == DEVICE_STOCK_COUNT)
		atomic_set(&priv->rec_count, 0);

	wake_up_interruptible_all(&priv->devread_wait);

	spin_unlock(&priv->dev_read_lock);
}