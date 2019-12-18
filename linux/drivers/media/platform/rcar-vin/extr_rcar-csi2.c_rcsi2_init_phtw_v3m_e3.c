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
 int /*<<< orphan*/  phtw_mbps_v3m_e3 ; 
 int rcsi2_phtw_write_mbps (struct rcar_csi2*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rcsi2_init_phtw_v3m_e3(struct rcar_csi2 *priv, unsigned int mbps)
{
	return rcsi2_phtw_write_mbps(priv, mbps, phtw_mbps_v3m_e3, 0x44);
}