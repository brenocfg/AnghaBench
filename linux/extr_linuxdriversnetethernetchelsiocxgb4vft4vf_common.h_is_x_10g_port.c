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
struct link_config {int /*<<< orphan*/  pcaps; } ;
typedef  int fw_port_cap32_t ;

/* Variables and functions */
 int FW_PORT_CAP32_SPEED_100M ; 
 int FW_PORT_CAP32_SPEED_1G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_G (int /*<<< orphan*/ ) ; 
 int FW_PORT_CAP32_SPEED_V (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_x_10g_port(const struct link_config *lc)
{
	fw_port_cap32_t speeds, high_speeds;

	speeds = FW_PORT_CAP32_SPEED_V(FW_PORT_CAP32_SPEED_G(lc->pcaps));
	high_speeds =
		speeds & ~(FW_PORT_CAP32_SPEED_100M | FW_PORT_CAP32_SPEED_1G);

	return high_speeds != 0;
}