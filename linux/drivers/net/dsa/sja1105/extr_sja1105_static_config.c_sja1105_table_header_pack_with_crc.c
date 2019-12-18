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
struct sja1105_table_header {int /*<<< orphan*/  crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACK ; 
 int SJA1105_SIZE_TABLE_HEADER ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sja1105_crc32 (void*,int) ; 
 int /*<<< orphan*/  sja1105_pack (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sja1105_table_header_packing (void*,struct sja1105_table_header*,int /*<<< orphan*/ ) ; 

void
sja1105_table_header_pack_with_crc(void *buf, struct sja1105_table_header *hdr)
{
	/* First pack the table as-is, then calculate the CRC, and
	 * finally put the proper CRC into the packed buffer
	 */
	memset(buf, 0, SJA1105_SIZE_TABLE_HEADER);
	sja1105_table_header_packing(buf, hdr, PACK);
	hdr->crc = sja1105_crc32(buf, SJA1105_SIZE_TABLE_HEADER - 4);
	sja1105_pack(buf + SJA1105_SIZE_TABLE_HEADER - 4, &hdr->crc, 31, 0, 4);
}