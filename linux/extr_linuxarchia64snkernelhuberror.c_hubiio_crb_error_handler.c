#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hubdev_info {int /*<<< orphan*/  hdi_nasid; } ;
typedef  int /*<<< orphan*/  nasid_t ;
typedef  int /*<<< orphan*/  ioerror_t ;
struct TYPE_6__ {void* ii_icrb0_e_regval; } ;
typedef  TYPE_1__ ii_icrb0_e_u_t ;
struct TYPE_7__ {scalar_t__ d_bteop; void* ii_icrb0_d_regval; } ;
typedef  TYPE_2__ ii_icrb0_d_u_t ;
struct TYPE_8__ {int c_btenum; void* ii_icrb0_c_regval; } ;
typedef  TYPE_3__ ii_icrb0_c_u_t ;
struct TYPE_9__ {scalar_t__ b_mark; int b_initiator; scalar_t__ b_imsgtype; int /*<<< orphan*/  b_ecode; void* ii_icrb0_b_regval; } ;
typedef  TYPE_4__ ii_icrb0_b_u_t ;
struct TYPE_10__ {void* ii_icrb0_a_regval; } ;
typedef  TYPE_5__ ii_icrb0_a_u_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_ICRB_A (int) ; 
 int /*<<< orphan*/  IIO_ICRB_B (int) ; 
 int /*<<< orphan*/  IIO_ICRB_C (int) ; 
 int /*<<< orphan*/  IIO_ICRB_D (int) ; 
 int /*<<< orphan*/  IIO_ICRB_E (int) ; 
 scalar_t__ IIO_ICRB_IMSGT_BTE ; 
 scalar_t__ IIO_ICRB_IMSGT_SN1NET ; 
 int IIO_ICRB_INIT_BTE0 ; 
 int IIO_ICRB_INIT_BTE1 ; 
 int IIO_NUM_CRBS ; 
 int /*<<< orphan*/  IOERROR_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOERROR_SETVALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* REMOTE_HUB_L (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bte_crb_error_handler (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  errortype ; 
 int /*<<< orphan*/  hubiio_crb_free (struct hubdev_info*,int) ; 
 int /*<<< orphan*/  nasid_to_cnodeid (int /*<<< orphan*/ ) ; 

void hubiio_crb_error_handler(struct hubdev_info *hubdev_info)
{
	nasid_t nasid;
	ii_icrb0_a_u_t icrba;	/* II CRB Register A */
	ii_icrb0_b_u_t icrbb;	/* II CRB Register B */
	ii_icrb0_c_u_t icrbc;	/* II CRB Register C */
	ii_icrb0_d_u_t icrbd;	/* II CRB Register D */
	ii_icrb0_e_u_t icrbe;	/* II CRB Register D */
	int i;
	int num_errors = 0;	/* Num of errors handled */
	ioerror_t ioerror;

	nasid = hubdev_info->hdi_nasid;

	/*
	 * XXX - Add locking for any recovery actions
	 */
	/*
	 * Scan through all CRBs in the Hub, and handle the errors
	 * in any of the CRBs marked.
	 */
	for (i = 0; i < IIO_NUM_CRBS; i++) {
		/* Check this crb entry to see if it is in error. */
		icrbb.ii_icrb0_b_regval = REMOTE_HUB_L(nasid, IIO_ICRB_B(i));

		if (icrbb.b_mark == 0) {
			continue;
		}

		icrba.ii_icrb0_a_regval = REMOTE_HUB_L(nasid, IIO_ICRB_A(i));

		IOERROR_INIT(&ioerror);

		/* read other CRB error registers. */
		icrbc.ii_icrb0_c_regval = REMOTE_HUB_L(nasid, IIO_ICRB_C(i));
		icrbd.ii_icrb0_d_regval = REMOTE_HUB_L(nasid, IIO_ICRB_D(i));
		icrbe.ii_icrb0_e_regval = REMOTE_HUB_L(nasid, IIO_ICRB_E(i));

		IOERROR_SETVALUE(&ioerror, errortype, icrbb.b_ecode);

		/* Check if this error is due to BTE operation,
		 * and handle it separately.
		 */
		if (icrbd.d_bteop ||
		    ((icrbb.b_initiator == IIO_ICRB_INIT_BTE0 ||
		      icrbb.b_initiator == IIO_ICRB_INIT_BTE1) &&
		     (icrbb.b_imsgtype == IIO_ICRB_IMSGT_BTE ||
		      icrbb.b_imsgtype == IIO_ICRB_IMSGT_SN1NET))) {

			int bte_num;

			if (icrbd.d_bteop)
				bte_num = icrbc.c_btenum;
			else	/* b_initiator bit 2 gives BTE number */
				bte_num = (icrbb.b_initiator & 0x4) >> 2;

			hubiio_crb_free(hubdev_info, i);

			bte_crb_error_handler(nasid_to_cnodeid(nasid), bte_num,
					      i, &ioerror, icrbd.d_bteop);
			num_errors++;
			continue;
		}
	}
}