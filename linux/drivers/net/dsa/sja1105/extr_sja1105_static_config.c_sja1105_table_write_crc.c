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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_crc32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sja1105_pack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sja1105_table_write_crc(u8 *table_start, u8 *crc_ptr)
{
	u64 computed_crc;
	int len_bytes;

	len_bytes = (uintptr_t)(crc_ptr - table_start);
	computed_crc = sja1105_crc32(table_start, len_bytes);
	sja1105_pack(crc_ptr, &computed_crc, 31, 0, 4);
}