#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  udp_sport ;
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  addr4; } ;
struct mlxsw_sp_nve_config {TYPE_1__ ul_sip; int /*<<< orphan*/  ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_TNGCR_TYPE_VXLAN ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_tngcr_nve_udp_sport_prefix_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_tngcr_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tngcr_usipv4_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_nve_vxlan_config_prepare(char *tngcr_pl,
				  const struct mlxsw_sp_nve_config *config)
{
	u8 udp_sport;

	mlxsw_reg_tngcr_pack(tngcr_pl, MLXSW_REG_TNGCR_TYPE_VXLAN, true,
			     config->ttl);
	/* VxLAN driver's default UDP source port range is 32768 (0x8000)
	 * to 60999 (0xee47). Set the upper 8 bits of the UDP source port
	 * to a random number between 0x80 and 0xee
	 */
	get_random_bytes(&udp_sport, sizeof(udp_sport));
	udp_sport = (udp_sport % (0xee - 0x80 + 1)) + 0x80;
	mlxsw_reg_tngcr_nve_udp_sport_prefix_set(tngcr_pl, udp_sport);
	mlxsw_reg_tngcr_usipv4_set(tngcr_pl, be32_to_cpu(config->ul_sip.addr4));
}