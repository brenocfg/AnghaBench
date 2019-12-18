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
struct meson_drm {int compat; } ;
typedef  enum vpu_compatible { ____Placeholder_vpu_compatible } vpu_compatible ;

/* Variables and functions */

__attribute__((used)) static inline int meson_vpu_is_compatible(struct meson_drm *priv,
					  enum vpu_compatible family)
{
	return priv->compat == family;
}