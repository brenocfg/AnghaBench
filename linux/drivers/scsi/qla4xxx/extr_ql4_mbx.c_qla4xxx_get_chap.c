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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int flt_region_chap; int flt_chap_size; } ;
struct scsi_qla_host {int port_num; int /*<<< orphan*/  chap_dma_pool; TYPE_1__ hw; } ;
struct ql4_chap_table {int /*<<< orphan*/  cookie; int /*<<< orphan*/  name; int /*<<< orphan*/  secret; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ CHAP_VALID_COOKIE ; 
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FLASH_CHAP_OFFSET ; 
 int FLASH_RAW_ACCESS_ADDR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  QL4_CHAP_MAX_NAME_LEN ; 
 int /*<<< orphan*/  QL4_CHAP_MAX_SECRET_LEN ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  __constant_cpu_to_le16 (scalar_t__) ; 
 scalar_t__ __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct ql4_chap_table*,int /*<<< orphan*/ ) ; 
 struct ql4_chap_table* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,...) ; 
 int qla4xxx_get_flash (struct scsi_qla_host*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qla4xxx_get_chap(struct scsi_qla_host *ha, char *username, char *password,
		     uint16_t idx)
{
	int ret = 0;
	int rval = QLA_ERROR;
	uint32_t offset = 0, chap_size;
	struct ql4_chap_table *chap_table;
	dma_addr_t chap_dma;

	chap_table = dma_pool_zalloc(ha->chap_dma_pool, GFP_KERNEL, &chap_dma);
	if (chap_table == NULL)
		return -ENOMEM;

	chap_size = sizeof(struct ql4_chap_table);

	if (is_qla40XX(ha))
		offset = FLASH_CHAP_OFFSET | (idx * chap_size);
	else {
		offset = FLASH_RAW_ACCESS_ADDR + (ha->hw.flt_region_chap << 2);
		/* flt_chap_size is CHAP table size for both ports
		 * so divide it by 2 to calculate the offset for second port
		 */
		if (ha->port_num == 1)
			offset += (ha->hw.flt_chap_size / 2);
		offset += (idx * chap_size);
	}

	rval = qla4xxx_get_flash(ha, chap_dma, offset, chap_size);
	if (rval != QLA_SUCCESS) {
		ret = -EINVAL;
		goto exit_get_chap;
	}

	DEBUG2(ql4_printk(KERN_INFO, ha, "Chap Cookie: x%x\n",
		__le16_to_cpu(chap_table->cookie)));

	if (__le16_to_cpu(chap_table->cookie) != CHAP_VALID_COOKIE) {
		ql4_printk(KERN_ERR, ha, "No valid chap entry found\n");
		goto exit_get_chap;
	}

	strlcpy(password, chap_table->secret, QL4_CHAP_MAX_SECRET_LEN);
	strlcpy(username, chap_table->name, QL4_CHAP_MAX_NAME_LEN);
	chap_table->cookie = __constant_cpu_to_le16(CHAP_VALID_COOKIE);

exit_get_chap:
	dma_pool_free(ha->chap_dma_pool, chap_table, chap_dma);
	return ret;
}