#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lan9303_mdio {TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int lan9303_mdio_real_read (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan9303_mdio_read(void *ctx, uint32_t reg, uint32_t *val)
{
	struct lan9303_mdio *sw_dev = (struct lan9303_mdio *)ctx;

	reg <<= 2; /* reg num to offset */
	mutex_lock(&sw_dev->device->bus->mdio_lock);
	*val = lan9303_mdio_real_read(sw_dev->device, reg);
	*val |= (lan9303_mdio_real_read(sw_dev->device, reg + 2) << 16);
	mutex_unlock(&sw_dev->device->bus->mdio_lock);

	return 0;
}