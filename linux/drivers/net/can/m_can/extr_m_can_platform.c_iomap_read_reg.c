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
typedef  int /*<<< orphan*/  u32 ;
struct m_can_plat_priv {scalar_t__ base; } ;
struct m_can_classdev {struct m_can_plat_priv* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 iomap_read_reg(struct m_can_classdev *cdev, int reg)
{
	struct m_can_plat_priv *priv = cdev->device_data;

	return readl(priv->base + reg);
}