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
struct rcar_csi2 {int dummy; } ;

/* Variables and functions */
 int __rcsi2_init_phtw_h3_v3h_m3n (struct rcar_csi2*,unsigned int) ; 

__attribute__((used)) static int rcsi2_init_phtw_h3_v3h_m3n(struct rcar_csi2 *priv, unsigned int mbps)
{
	return __rcsi2_init_phtw_h3_v3h_m3n(priv, mbps);
}