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
typedef  int /*<<< orphan*/  u32 ;
struct w5100_priv {TYPE_1__* ops; } ;
struct TYPE_2__ {int chip_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ RTR_DEFAULT ; 
#define  W5100 130 
 int /*<<< orphan*/  W5100_RTR ; 
#define  W5200 129 
#define  W5500 128 
 int /*<<< orphan*/  W5500_RTR ; 
 int /*<<< orphan*/  w5100_disable_intr (struct w5100_priv*) ; 
 int /*<<< orphan*/  w5100_memory_configure (struct w5100_priv*) ; 
 scalar_t__ w5100_read16 (struct w5100_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5100_reset (struct w5100_priv*) ; 
 int /*<<< orphan*/  w5100_write_macaddr (struct w5100_priv*) ; 
 int /*<<< orphan*/  w5200_memory_configure (struct w5100_priv*) ; 
 int /*<<< orphan*/  w5500_memory_configure (struct w5100_priv*) ; 

__attribute__((used)) static int w5100_hw_reset(struct w5100_priv *priv)
{
	u32 rtr;

	w5100_reset(priv);

	w5100_disable_intr(priv);
	w5100_write_macaddr(priv);

	switch (priv->ops->chip_id) {
	case W5100:
		w5100_memory_configure(priv);
		rtr = W5100_RTR;
		break;
	case W5200:
		w5200_memory_configure(priv);
		rtr = W5100_RTR;
		break;
	case W5500:
		w5500_memory_configure(priv);
		rtr = W5500_RTR;
		break;
	default:
		return -EINVAL;
	}

	if (w5100_read16(priv, rtr) != RTR_DEFAULT)
		return -ENODEV;

	return 0;
}