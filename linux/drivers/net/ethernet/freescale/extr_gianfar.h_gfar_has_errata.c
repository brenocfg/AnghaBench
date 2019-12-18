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
struct gfar_private {int errata; } ;
typedef  enum gfar_errata { ____Placeholder_gfar_errata } gfar_errata ;

/* Variables and functions */

__attribute__((used)) static inline int gfar_has_errata(struct gfar_private *priv,
				  enum gfar_errata err)
{
	return priv->errata & err;
}