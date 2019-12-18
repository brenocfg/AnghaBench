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
typedef  int uint16_t ;
struct dev_db_entry {int /*<<< orphan*/  port; int /*<<< orphan*/ * isid; int /*<<< orphan*/ * ip_addr; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int DDB_OPT_IPV6_DEVICE ; 
 size_t IP_ADDR_LEN ; 
 size_t IPv6_ADDR_LEN ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int qla4xxx_cmp_fw_stentry(struct dev_db_entry *fw_ddb_entry,
				  struct dev_db_entry *flash_ddb_entry)
{
	uint16_t options = 0;
	size_t ip_len = IP_ADDR_LEN;

	options = le16_to_cpu(fw_ddb_entry->options);
	if (options & DDB_OPT_IPV6_DEVICE)
		ip_len = IPv6_ADDR_LEN;

	if (memcmp(fw_ddb_entry->ip_addr, flash_ddb_entry->ip_addr, ip_len))
		return QLA_ERROR;

	if (memcmp(&fw_ddb_entry->isid[0], &flash_ddb_entry->isid[0],
		   sizeof(fw_ddb_entry->isid)))
		return QLA_ERROR;

	if (memcmp(&fw_ddb_entry->port, &flash_ddb_entry->port,
		   sizeof(fw_ddb_entry->port)))
		return QLA_ERROR;

	return QLA_SUCCESS;
}