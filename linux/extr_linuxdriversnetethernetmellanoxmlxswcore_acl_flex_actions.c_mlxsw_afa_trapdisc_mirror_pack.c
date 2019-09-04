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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_trapdisc_mirror_agent_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_trapdisc_mirror_enable_set (char*,int) ; 

__attribute__((used)) static inline void
mlxsw_afa_trapdisc_mirror_pack(char *payload, bool mirror_enable,
			       u8 mirror_agent)
{
	mlxsw_afa_trapdisc_mirror_enable_set(payload, mirror_enable);
	mlxsw_afa_trapdisc_mirror_agent_set(payload, mirror_agent);
}