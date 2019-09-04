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
struct m_can_priv {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m_can_clk_stop(struct m_can_priv *priv)
{
	pm_runtime_put_sync(priv->device);
}