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
typedef  int uint16_t ;
struct TYPE_2__ {int flt_chap_size; } ;
struct scsi_qla_host {int /*<<< orphan*/  chap_sem; scalar_t__ chap_list; TYPE_1__ hw; } ;
struct ql4_chap_table {scalar_t__ cookie; int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  secret; } ;

/* Variables and functions */
 int BIT_6 ; 
 int BIT_7 ; 
 int /*<<< orphan*/  CHAP_VALID_COOKIE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_CHAP_ENTRIES_40XX ; 
 int /*<<< orphan*/  MAX_CHAP_NAME_LEN ; 
 int /*<<< orphan*/  MAX_CHAP_SECRET_LEN ; 
 int MAX_RESRV_CHAP_IDX ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ __constant_cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_qla80XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int qla4xxx_set_chap (struct scsi_qla_host*,char*,char*,int,int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int qla4xxx_get_chap_index(struct scsi_qla_host *ha, char *username,
			   char *password, int bidi, uint16_t *chap_index)
{
	int i, rval;
	int free_index = -1;
	int found_index = 0;
	int max_chap_entries = 0;
	struct ql4_chap_table *chap_table;

	if (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
						sizeof(struct ql4_chap_table);
	else
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	if (!ha->chap_list) {
		ql4_printk(KERN_ERR, ha, "Do not have CHAP table cache\n");
		return QLA_ERROR;
	}

	if (!username || !password) {
		ql4_printk(KERN_ERR, ha, "Do not have username and psw\n");
		return QLA_ERROR;
	}

	mutex_lock(&ha->chap_sem);
	for (i = 0; i < max_chap_entries; i++) {
		chap_table = (struct ql4_chap_table *)ha->chap_list + i;
		if (chap_table->cookie !=
		    __constant_cpu_to_le16(CHAP_VALID_COOKIE)) {
			if (i > MAX_RESRV_CHAP_IDX && free_index == -1)
				free_index = i;
			continue;
		}
		if (bidi) {
			if (chap_table->flags & BIT_7)
				continue;
		} else {
			if (chap_table->flags & BIT_6)
				continue;
		}
		if (!strncmp(chap_table->secret, password,
			     MAX_CHAP_SECRET_LEN) &&
		    !strncmp(chap_table->name, username,
			     MAX_CHAP_NAME_LEN)) {
			*chap_index = i;
			found_index = 1;
			break;
		}
	}

	/* If chap entry is not present and a free index is available then
	 * write the entry in flash
	 */
	if (!found_index && free_index != -1) {
		rval = qla4xxx_set_chap(ha, username, password,
					free_index, bidi);
		if (!rval) {
			*chap_index = free_index;
			found_index = 1;
		}
	}

	mutex_unlock(&ha->chap_sem);

	if (found_index)
		return QLA_SUCCESS;
	return QLA_ERROR;
}