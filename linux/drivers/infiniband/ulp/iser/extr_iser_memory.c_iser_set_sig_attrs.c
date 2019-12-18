#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int prot_flags; } ;
struct TYPE_4__ {void* bg_type; } ;
struct TYPE_5__ {TYPE_1__ dif; } ;
struct TYPE_6__ {TYPE_2__ sig; void* sig_type; } ;
struct ib_sig_attrs {TYPE_3__ mem; TYPE_3__ wire; } ;

/* Variables and functions */
 int EINVAL ; 
 void* IB_SIG_TYPE_NONE ; 
 void* IB_T10DIF_CRC ; 
 void* IB_T10DIF_CSUM ; 
 int SCSI_PROT_IP_CHECKSUM ; 
#define  SCSI_PROT_READ_INSERT 133 
#define  SCSI_PROT_READ_PASS 132 
#define  SCSI_PROT_READ_STRIP 131 
#define  SCSI_PROT_WRITE_INSERT 130 
#define  SCSI_PROT_WRITE_PASS 129 
#define  SCSI_PROT_WRITE_STRIP 128 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  iser_set_dif_domain (struct scsi_cmnd*,TYPE_3__*) ; 
 int scsi_get_prot_op (struct scsi_cmnd*) ; 

__attribute__((used)) static int
iser_set_sig_attrs(struct scsi_cmnd *sc, struct ib_sig_attrs *sig_attrs)
{
	switch (scsi_get_prot_op(sc)) {
	case SCSI_PROT_WRITE_INSERT:
	case SCSI_PROT_READ_STRIP:
		sig_attrs->mem.sig_type = IB_SIG_TYPE_NONE;
		iser_set_dif_domain(sc, &sig_attrs->wire);
		sig_attrs->wire.sig.dif.bg_type = IB_T10DIF_CRC;
		break;
	case SCSI_PROT_READ_INSERT:
	case SCSI_PROT_WRITE_STRIP:
		sig_attrs->wire.sig_type = IB_SIG_TYPE_NONE;
		iser_set_dif_domain(sc, &sig_attrs->mem);
		sig_attrs->mem.sig.dif.bg_type = sc->prot_flags & SCSI_PROT_IP_CHECKSUM ?
						IB_T10DIF_CSUM : IB_T10DIF_CRC;
		break;
	case SCSI_PROT_READ_PASS:
	case SCSI_PROT_WRITE_PASS:
		iser_set_dif_domain(sc, &sig_attrs->wire);
		sig_attrs->wire.sig.dif.bg_type = IB_T10DIF_CRC;
		iser_set_dif_domain(sc, &sig_attrs->mem);
		sig_attrs->mem.sig.dif.bg_type = sc->prot_flags & SCSI_PROT_IP_CHECKSUM ?
						IB_T10DIF_CSUM : IB_T10DIF_CRC;
		break;
	default:
		iser_err("Unsupported PI operation %d\n",
			 scsi_get_prot_op(sc));
		return -EINVAL;
	}

	return 0;
}