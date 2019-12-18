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
typedef  void* u32 ;
struct scsi_cmnd {int /*<<< orphan*/  request; } ;
struct hisi_sas_protect_iu_v3_hw {int dw0; int /*<<< orphan*/  dw4; void* lbrtcv; void* lbrtgv; } ;

/* Variables and functions */
 int INCR_LBRT_MSK ; 
#define  SCSI_PROT_READ_INSERT 133 
#define  SCSI_PROT_READ_PASS 132 
#define  SCSI_PROT_READ_STRIP 131 
#define  SCSI_PROT_WRITE_INSERT 130 
#define  SCSI_PROT_WRITE_PASS 129 
#define  SCSI_PROT_WRITE_STRIP 128 
 int T10_CHK_EN_MSK ; 
 int T10_INSRT_EN_MSK ; 
 int T10_RMV_EN_MSK ; 
 int USR_DATA_BLOCK_SZ_OFF ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 int /*<<< orphan*/  get_prot_chk_msk_v3_hw (struct scsi_cmnd*) ; 
 unsigned char scsi_get_prot_op (struct scsi_cmnd*) ; 
 unsigned int scsi_prot_interval (struct scsi_cmnd*) ; 
 void* t10_pi_ref_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_prot_v3_hw(struct scsi_cmnd *scsi_cmnd,
			    struct hisi_sas_protect_iu_v3_hw *prot)
{
	unsigned char prot_op = scsi_get_prot_op(scsi_cmnd);
	unsigned int interval = scsi_prot_interval(scsi_cmnd);
	u32 lbrt_chk_val = t10_pi_ref_tag(scsi_cmnd->request);

	switch (prot_op) {
	case SCSI_PROT_READ_INSERT:
		prot->dw0 |= T10_INSRT_EN_MSK;
		prot->lbrtgv = lbrt_chk_val;
		break;
	case SCSI_PROT_READ_STRIP:
		prot->dw0 |= (T10_RMV_EN_MSK | T10_CHK_EN_MSK);
		prot->lbrtcv = lbrt_chk_val;
		prot->dw4 |= get_prot_chk_msk_v3_hw(scsi_cmnd);
		break;
	case SCSI_PROT_READ_PASS:
		prot->dw0 |= T10_CHK_EN_MSK;
		prot->lbrtcv = lbrt_chk_val;
		prot->dw4 |= get_prot_chk_msk_v3_hw(scsi_cmnd);
		break;
	case SCSI_PROT_WRITE_INSERT:
		prot->dw0 |= T10_INSRT_EN_MSK;
		prot->lbrtgv = lbrt_chk_val;
		break;
	case SCSI_PROT_WRITE_STRIP:
		prot->dw0 |= (T10_RMV_EN_MSK | T10_CHK_EN_MSK);
		prot->lbrtcv = lbrt_chk_val;
		break;
	case SCSI_PROT_WRITE_PASS:
		prot->dw0 |= T10_CHK_EN_MSK;
		prot->lbrtcv = lbrt_chk_val;
		prot->dw4 |= get_prot_chk_msk_v3_hw(scsi_cmnd);
		break;
	default:
		WARN(1, "prot_op(0x%x) is not valid\n", prot_op);
		break;
	}

	switch (interval) {
	case 512:
		break;
	case 4096:
		prot->dw0 |= (0x1 << USR_DATA_BLOCK_SZ_OFF);
		break;
	case 520:
		prot->dw0 |= (0x2 << USR_DATA_BLOCK_SZ_OFF);
		break;
	default:
		WARN(1, "protection interval (0x%x) invalid\n",
		     interval);
		break;
	}

	prot->dw0 |= INCR_LBRT_MSK;
}