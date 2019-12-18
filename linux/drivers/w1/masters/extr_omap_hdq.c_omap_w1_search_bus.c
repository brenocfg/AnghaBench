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
typedef  int /*<<< orphan*/  (* w1_slave_found_callback ) (struct w1_master*,int) ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct w1_master {int dummy; } ;

/* Variables and functions */
 int cpu_to_le64 (int) ; 
 int w1_calc_crc8 (int /*<<< orphan*/ *,int) ; 
 int w1_id ; 

__attribute__((used)) static void omap_w1_search_bus(void *_hdq, struct w1_master *master_dev,
		u8 search_type, w1_slave_found_callback slave_found)
{
	u64 module_id, rn_le, cs, id;

	if (w1_id)
		module_id = w1_id;
	else
		module_id = 0x1;

	rn_le = cpu_to_le64(module_id);
	/*
	 * HDQ might not obey truly the 1-wire spec.
	 * So calculate CRC based on module parameter.
	 */
	cs = w1_calc_crc8((u8 *)&rn_le, 7);
	id = (cs << 56) | module_id;

	slave_found(master_dev, id);
}