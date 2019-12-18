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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_mib_desc {int size; int /*<<< orphan*/  offset; } ;
struct b53_device {int /*<<< orphan*/  stats_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_MIB_PAGE (int) ; 
 struct b53_mib_desc* b53_get_mib (struct b53_device*) ; 
 unsigned int b53_get_mib_size (struct b53_device*) ; 
 int /*<<< orphan*/  b53_read32 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  b53_read64 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void b53_get_ethtool_stats(struct dsa_switch *ds, int port, uint64_t *data)
{
	struct b53_device *dev = ds->priv;
	const struct b53_mib_desc *mibs = b53_get_mib(dev);
	unsigned int mib_size = b53_get_mib_size(dev);
	const struct b53_mib_desc *s;
	unsigned int i;
	u64 val = 0;

	if (is5365(dev) && port == 5)
		port = 8;

	mutex_lock(&dev->stats_mutex);

	for (i = 0; i < mib_size; i++) {
		s = &mibs[i];

		if (s->size == 8) {
			b53_read64(dev, B53_MIB_PAGE(port), s->offset, &val);
		} else {
			u32 val32;

			b53_read32(dev, B53_MIB_PAGE(port), s->offset,
				   &val32);
			val = val32;
		}
		data[i] = (u64)val;
	}

	mutex_unlock(&dev->stats_mutex);
}