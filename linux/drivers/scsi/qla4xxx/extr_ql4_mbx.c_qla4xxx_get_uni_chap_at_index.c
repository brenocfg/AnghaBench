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
 int BIT_7 ; 
 int /*<<< orphan*/  CHAP_VALID_COOKIE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_CHAP_ENTRIES_40XX ; 
 int /*<<< orphan*/  MAX_CHAP_NAME_LEN ; 
 int /*<<< orphan*/  MAX_CHAP_SECRET_LEN ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ __constant_cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_qla80XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qla4xxx_get_uni_chap_at_index(struct scsi_qla_host *ha, char *username,
				  char *password, uint16_t chap_index)
{
	int rval = QLA_ERROR;
	struct ql4_chap_table *chap_table = NULL;
	int max_chap_entries;

	if (!ha->chap_list) {
		ql4_printk(KERN_ERR, ha, "Do not have CHAP table cache\n");
		rval = QLA_ERROR;
		goto exit_uni_chap;
	}

	if (!username || !password) {
		ql4_printk(KERN_ERR, ha, "No memory for username & secret\n");
		rval = QLA_ERROR;
		goto exit_uni_chap;
	}

	if (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
				   sizeof(struct ql4_chap_table);
	else
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	if (chap_index > max_chap_entries) {
		ql4_printk(KERN_ERR, ha, "Invalid Chap index\n");
		rval = QLA_ERROR;
		goto exit_uni_chap;
	}

	mutex_lock(&ha->chap_sem);
	chap_table = (struct ql4_chap_table *)ha->chap_list + chap_index;
	if (chap_table->cookie != __constant_cpu_to_le16(CHAP_VALID_COOKIE)) {
		rval = QLA_ERROR;
		goto exit_unlock_uni_chap;
	}

	if (!(chap_table->flags & BIT_7)) {
		ql4_printk(KERN_ERR, ha, "Unidirectional entry not set\n");
		rval = QLA_ERROR;
		goto exit_unlock_uni_chap;
	}

	strlcpy(password, chap_table->secret, MAX_CHAP_SECRET_LEN);
	strlcpy(username, chap_table->name, MAX_CHAP_NAME_LEN);

	rval = QLA_SUCCESS;

exit_unlock_uni_chap:
	mutex_unlock(&ha->chap_sem);
exit_uni_chap:
	return rval;
}