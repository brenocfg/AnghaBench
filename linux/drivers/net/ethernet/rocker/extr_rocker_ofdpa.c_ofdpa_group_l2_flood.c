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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ofdpa_group_l2_fan_out (struct ofdpa_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_group_l2_flood(struct ofdpa_port *ofdpa_port,
				int flags, __be16 vlan_id,
				u8 group_count,	const u32 *group_ids,
				u32 group_id)
{
	return ofdpa_group_l2_fan_out(ofdpa_port, flags,
				      group_count, group_ids,
				      group_id);
}