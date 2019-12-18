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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_device {int dummy; } ;
struct c8_inquiry {int page_code; char* page_id; char* array_user_label; int /*<<< orphan*/  array_uniq_id_len; int /*<<< orphan*/  array_unique_id; int /*<<< orphan*/ * lun; } ;
struct TYPE_2__ {struct c8_inquiry c8; } ;
struct rdac_dh_data {int /*<<< orphan*/  lun; TYPE_1__ inq; } ;

/* Variables and functions */
 int ARRAY_LABEL_LEN ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_NOSYS ; 
 int SCSI_DH_OK ; 
 int /*<<< orphan*/  UNIQUE_ID_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_get_vpd_page (struct scsi_device*,int,unsigned char*,int) ; 

__attribute__((used)) static int get_lun_info(struct scsi_device *sdev, struct rdac_dh_data *h,
			char *array_name, u8 *array_id)
{
	int err = SCSI_DH_IO, i;
	struct c8_inquiry *inqp = &h->inq.c8;

	if (!scsi_get_vpd_page(sdev, 0xC8, (unsigned char *)inqp,
			       sizeof(struct c8_inquiry))) {
		if (inqp->page_code != 0xc8)
			return SCSI_DH_NOSYS;
		if (inqp->page_id[0] != 'e' || inqp->page_id[1] != 'd' ||
		    inqp->page_id[2] != 'i' || inqp->page_id[3] != 'd')
			return SCSI_DH_NOSYS;
		h->lun = inqp->lun[7]; /* Uses only the last byte */

		for(i=0; i<ARRAY_LABEL_LEN-1; ++i)
			*(array_name+i) = inqp->array_user_label[(2*i)+1];

		*(array_name+ARRAY_LABEL_LEN-1) = '\0';
		memset(array_id, 0, UNIQUE_ID_LEN);
		memcpy(array_id, inqp->array_unique_id, inqp->array_uniq_id_len);
		err = SCSI_DH_OK;
	}
	return err;
}