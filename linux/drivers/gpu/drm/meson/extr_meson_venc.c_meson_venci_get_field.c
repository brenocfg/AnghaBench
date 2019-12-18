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
struct meson_drm {scalar_t__ io_base; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  ENCI_INFO_READ ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 unsigned int readl_relaxed (scalar_t__) ; 

unsigned int meson_venci_get_field(struct meson_drm *priv)
{
	return readl_relaxed(priv->io_base + _REG(ENCI_INFO_READ)) & BIT(29);
}