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
typedef  int u32 ;
struct TYPE_2__ {int msg_id; } ;
struct bfi_mbmsg_s {TYPE_1__ mh; } ;
struct bfi_fru_rsp_s {int /*<<< orphan*/  length; int /*<<< orphan*/  status; } ;
struct bfa_fru_s {int residue; int status; int offset; int ubuf; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  op_busy; int /*<<< orphan*/  dbuf_kva; } ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFI_FRUVPD_H2I_READ_REQ ; 
 int /*<<< orphan*/  BFI_FRUVPD_H2I_WRITE_REQ ; 
#define  BFI_FRUVPD_I2H_READ_RSP 131 
#define  BFI_FRUVPD_I2H_WRITE_RSP 130 
 int /*<<< orphan*/  BFI_TFRU_H2I_READ_REQ ; 
 int /*<<< orphan*/  BFI_TFRU_H2I_WRITE_REQ ; 
#define  BFI_TFRU_I2H_READ_RSP 129 
#define  BFI_TFRU_I2H_WRITE_RSP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fru_read_send (struct bfa_fru_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fru_write_send (struct bfa_fru_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fru_s*,int) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 

void
bfa_fru_intr(void *fruarg, struct bfi_mbmsg_s *msg)
{
	struct bfa_fru_s *fru = fruarg;
	struct bfi_fru_rsp_s *rsp = (struct bfi_fru_rsp_s *)msg;
	u32 status;

	bfa_trc(fru, msg->mh.msg_id);

	if (!fru->op_busy) {
		/*
		 * receiving response after ioc failure
		 */
		bfa_trc(fru, 0x9999);
		return;
	}

	switch (msg->mh.msg_id) {
	case BFI_FRUVPD_I2H_WRITE_RSP:
	case BFI_TFRU_I2H_WRITE_RSP:
		status = be32_to_cpu(rsp->status);
		bfa_trc(fru, status);

		if (status != BFA_STATUS_OK || fru->residue == 0) {
			fru->status = status;
			fru->op_busy = 0;
			if (fru->cbfn)
				fru->cbfn(fru->cbarg, fru->status);
		} else {
			bfa_trc(fru, fru->offset);
			if (msg->mh.msg_id == BFI_FRUVPD_I2H_WRITE_RSP)
				bfa_fru_write_send(fru,
					BFI_FRUVPD_H2I_WRITE_REQ);
			else
				bfa_fru_write_send(fru,
					BFI_TFRU_H2I_WRITE_REQ);
		}
		break;
	case BFI_FRUVPD_I2H_READ_RSP:
	case BFI_TFRU_I2H_READ_RSP:
		status = be32_to_cpu(rsp->status);
		bfa_trc(fru, status);

		if (status != BFA_STATUS_OK) {
			fru->status = status;
			fru->op_busy = 0;
			if (fru->cbfn)
				fru->cbfn(fru->cbarg, fru->status);
		} else {
			u32 len = be32_to_cpu(rsp->length);

			bfa_trc(fru, fru->offset);
			bfa_trc(fru, len);

			memcpy(fru->ubuf + fru->offset, fru->dbuf_kva, len);
			fru->residue -= len;
			fru->offset += len;

			if (fru->residue == 0) {
				fru->status = status;
				fru->op_busy = 0;
				if (fru->cbfn)
					fru->cbfn(fru->cbarg, fru->status);
			} else {
				if (msg->mh.msg_id == BFI_FRUVPD_I2H_READ_RSP)
					bfa_fru_read_send(fru,
						BFI_FRUVPD_H2I_READ_REQ);
				else
					bfa_fru_read_send(fru,
						BFI_TFRU_H2I_READ_REQ);
			}
		}
		break;
	default:
		WARN_ON(1);
	}
}