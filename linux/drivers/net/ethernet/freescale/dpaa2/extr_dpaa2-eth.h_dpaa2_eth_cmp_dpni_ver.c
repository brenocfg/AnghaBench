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
typedef  scalar_t__ u16 ;
struct dpaa2_eth_priv {scalar_t__ dpni_ver_major; int dpni_ver_minor; } ;

/* Variables and functions */

__attribute__((used)) static inline int dpaa2_eth_cmp_dpni_ver(struct dpaa2_eth_priv *priv,
					 u16 ver_major, u16 ver_minor)
{
	if (priv->dpni_ver_major == ver_major)
		return priv->dpni_ver_minor - ver_minor;
	return priv->dpni_ver_major - ver_major;
}