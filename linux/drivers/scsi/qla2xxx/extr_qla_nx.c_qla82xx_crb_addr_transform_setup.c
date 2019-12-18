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

/* Variables and functions */
 int /*<<< orphan*/  C2C0 ; 
 int /*<<< orphan*/  C2C1 ; 
 int /*<<< orphan*/  CAM ; 
 int /*<<< orphan*/  CAS0 ; 
 int /*<<< orphan*/  CAS1 ; 
 int /*<<< orphan*/  CAS2 ; 
 int /*<<< orphan*/  EG ; 
 int /*<<< orphan*/  I2C0 ; 
 int /*<<< orphan*/  I2Q ; 
 int /*<<< orphan*/  MN ; 
 int /*<<< orphan*/  MS ; 
 int /*<<< orphan*/  NIU ; 
 int /*<<< orphan*/  OCM0 ; 
 int /*<<< orphan*/  PGN0 ; 
 int /*<<< orphan*/  PGN1 ; 
 int /*<<< orphan*/  PGN2 ; 
 int /*<<< orphan*/  PGN3 ; 
 int /*<<< orphan*/  PGND ; 
 int /*<<< orphan*/  PGNI ; 
 int /*<<< orphan*/  PGS0 ; 
 int /*<<< orphan*/  PGS1 ; 
 int /*<<< orphan*/  PGS2 ; 
 int /*<<< orphan*/  PGS3 ; 
 int /*<<< orphan*/  PGSD ; 
 int /*<<< orphan*/  PGSI ; 
 int /*<<< orphan*/  PH ; 
 int /*<<< orphan*/  PS ; 
 int /*<<< orphan*/  QMN ; 
 int /*<<< orphan*/  QMS ; 
 int /*<<< orphan*/  ROMUSB ; 
 int /*<<< orphan*/  RPMX0 ; 
 int /*<<< orphan*/  RPMX1 ; 
 int /*<<< orphan*/  RPMX2 ; 
 int /*<<< orphan*/  RPMX3 ; 
 int /*<<< orphan*/  RPMX4 ; 
 int /*<<< orphan*/  RPMX5 ; 
 int /*<<< orphan*/  RPMX6 ; 
 int /*<<< orphan*/  RPMX7 ; 
 int /*<<< orphan*/  SMB ; 
 int /*<<< orphan*/  SN ; 
 int /*<<< orphan*/  SQN0 ; 
 int /*<<< orphan*/  SQN1 ; 
 int /*<<< orphan*/  SQN2 ; 
 int /*<<< orphan*/  SQN3 ; 
 int /*<<< orphan*/  SQS0 ; 
 int /*<<< orphan*/  SQS1 ; 
 int /*<<< orphan*/  SQS2 ; 
 int /*<<< orphan*/  SQS3 ; 
 int /*<<< orphan*/  SRE ; 
 int /*<<< orphan*/  TIMR ; 
 int /*<<< orphan*/  XDMA ; 
 int /*<<< orphan*/  qla82xx_crb_addr_transform (int /*<<< orphan*/ ) ; 
 int qla82xx_crb_table_initialized ; 

__attribute__((used)) static void qla82xx_crb_addr_transform_setup(void)
{
	qla82xx_crb_addr_transform(XDMA);
	qla82xx_crb_addr_transform(TIMR);
	qla82xx_crb_addr_transform(SRE);
	qla82xx_crb_addr_transform(SQN3);
	qla82xx_crb_addr_transform(SQN2);
	qla82xx_crb_addr_transform(SQN1);
	qla82xx_crb_addr_transform(SQN0);
	qla82xx_crb_addr_transform(SQS3);
	qla82xx_crb_addr_transform(SQS2);
	qla82xx_crb_addr_transform(SQS1);
	qla82xx_crb_addr_transform(SQS0);
	qla82xx_crb_addr_transform(RPMX7);
	qla82xx_crb_addr_transform(RPMX6);
	qla82xx_crb_addr_transform(RPMX5);
	qla82xx_crb_addr_transform(RPMX4);
	qla82xx_crb_addr_transform(RPMX3);
	qla82xx_crb_addr_transform(RPMX2);
	qla82xx_crb_addr_transform(RPMX1);
	qla82xx_crb_addr_transform(RPMX0);
	qla82xx_crb_addr_transform(ROMUSB);
	qla82xx_crb_addr_transform(SN);
	qla82xx_crb_addr_transform(QMN);
	qla82xx_crb_addr_transform(QMS);
	qla82xx_crb_addr_transform(PGNI);
	qla82xx_crb_addr_transform(PGND);
	qla82xx_crb_addr_transform(PGN3);
	qla82xx_crb_addr_transform(PGN2);
	qla82xx_crb_addr_transform(PGN1);
	qla82xx_crb_addr_transform(PGN0);
	qla82xx_crb_addr_transform(PGSI);
	qla82xx_crb_addr_transform(PGSD);
	qla82xx_crb_addr_transform(PGS3);
	qla82xx_crb_addr_transform(PGS2);
	qla82xx_crb_addr_transform(PGS1);
	qla82xx_crb_addr_transform(PGS0);
	qla82xx_crb_addr_transform(PS);
	qla82xx_crb_addr_transform(PH);
	qla82xx_crb_addr_transform(NIU);
	qla82xx_crb_addr_transform(I2Q);
	qla82xx_crb_addr_transform(EG);
	qla82xx_crb_addr_transform(MN);
	qla82xx_crb_addr_transform(MS);
	qla82xx_crb_addr_transform(CAS2);
	qla82xx_crb_addr_transform(CAS1);
	qla82xx_crb_addr_transform(CAS0);
	qla82xx_crb_addr_transform(CAM);
	qla82xx_crb_addr_transform(C2C1);
	qla82xx_crb_addr_transform(C2C0);
	qla82xx_crb_addr_transform(SMB);
	qla82xx_crb_addr_transform(OCM0);
	/*
	 * Used only in P3 just define it for P2 also.
	 */
	qla82xx_crb_addr_transform(I2C0);

	qla82xx_crb_table_initialized = 1;
}