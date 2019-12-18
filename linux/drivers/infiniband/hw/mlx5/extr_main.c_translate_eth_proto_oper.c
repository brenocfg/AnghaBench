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

/* Variables and functions */
 int translate_eth_ext_proto_oper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int translate_eth_legacy_proto_oper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int translate_eth_proto_oper(u32 eth_proto_oper, u8 *active_speed,
				    u8 *active_width, bool ext)
{
	return ext ?
		translate_eth_ext_proto_oper(eth_proto_oper, active_speed,
					     active_width) :
		translate_eth_legacy_proto_oper(eth_proto_oper, active_speed,
						active_width);
}