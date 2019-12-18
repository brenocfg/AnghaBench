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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct ql4_tuple_ddb {int /*<<< orphan*/ * isid; void* port; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/ * iscsi_name; int /*<<< orphan*/  tpgt; } ;
struct dev_db_entry {int /*<<< orphan*/ * isid; int /*<<< orphan*/  port; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  options; int /*<<< orphan*/ * iscsi_name; int /*<<< orphan*/  tgt_portal_grp; } ;

/* Variables and functions */
 int DDB_OPT_IPV6_DEVICE ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4xxx_convert_param_ddb(struct dev_db_entry *fw_ddb_entry,
				      struct ql4_tuple_ddb *tddb,
				      uint8_t *flash_isid)
{
	uint16_t options = 0;

	tddb->tpgt = le32_to_cpu(fw_ddb_entry->tgt_portal_grp);
	memcpy(&tddb->iscsi_name[0], &fw_ddb_entry->iscsi_name[0],
	       min(sizeof(tddb->iscsi_name), sizeof(fw_ddb_entry->iscsi_name)));

	options = le16_to_cpu(fw_ddb_entry->options);
	if (options & DDB_OPT_IPV6_DEVICE)
		sprintf(tddb->ip_addr, "%pI6", fw_ddb_entry->ip_addr);
	else
		sprintf(tddb->ip_addr, "%pI4", fw_ddb_entry->ip_addr);

	tddb->port = le16_to_cpu(fw_ddb_entry->port);

	if (flash_isid == NULL)
		memcpy(&tddb->isid[0], &fw_ddb_entry->isid[0],
		       sizeof(tddb->isid));
	else
		memcpy(&tddb->isid[0], &flash_isid[0], sizeof(tddb->isid));
}