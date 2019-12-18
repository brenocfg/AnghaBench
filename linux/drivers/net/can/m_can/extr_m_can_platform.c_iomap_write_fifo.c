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
struct m_can_plat_priv {scalar_t__ mram_base; } ;
struct m_can_classdev {struct m_can_plat_priv* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int iomap_write_fifo(struct m_can_classdev *cdev, int offset, int val)
{
	struct m_can_plat_priv *priv = cdev->device_data;

	writel(val, priv->mram_base + offset);

	return 0;
}