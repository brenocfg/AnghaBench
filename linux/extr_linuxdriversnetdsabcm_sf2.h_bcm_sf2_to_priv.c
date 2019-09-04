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
struct dsa_switch {struct b53_device* priv; } ;
struct bcm_sf2_priv {int dummy; } ;
struct b53_device {struct bcm_sf2_priv* priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct bcm_sf2_priv *bcm_sf2_to_priv(struct dsa_switch *ds)
{
	struct b53_device *dev = ds->priv;

	return dev->priv;
}