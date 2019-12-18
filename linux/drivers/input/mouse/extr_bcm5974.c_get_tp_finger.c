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
struct tp_finger {int dummy; } ;
struct bcm5974_config {int tp_header; int tp_delta; int tp_fsize; } ;
struct bcm5974 {int /*<<< orphan*/ * tp_data; struct bcm5974_config cfg; } ;

/* Variables and functions */

__attribute__((used)) static const struct tp_finger *get_tp_finger(const struct bcm5974 *dev, int i)
{
	const struct bcm5974_config *c = &dev->cfg;
	u8 *f_base = dev->tp_data + c->tp_header + c->tp_delta;

	return (const struct tp_finger *)(f_base + i * c->tp_fsize);
}