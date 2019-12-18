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
struct g12a_mdio_mux {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MESON_G12A_MDIO_EXTERNAL_ID 129 
#define  MESON_G12A_MDIO_INTERNAL_ID 128 
 struct g12a_mdio_mux* dev_get_drvdata (void*) ; 
 int g12a_enable_external_mdio (struct g12a_mdio_mux*) ; 
 int g12a_enable_internal_mdio (struct g12a_mdio_mux*) ; 

__attribute__((used)) static int g12a_mdio_switch_fn(int current_child, int desired_child,
			       void *data)
{
	struct g12a_mdio_mux *priv = dev_get_drvdata(data);

	if (current_child == desired_child)
		return 0;

	switch (desired_child) {
	case MESON_G12A_MDIO_EXTERNAL_ID:
		return g12a_enable_external_mdio(priv);
	case MESON_G12A_MDIO_INTERNAL_ID:
		return g12a_enable_internal_mdio(priv);
	default:
		return -EINVAL;
	}
}