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
 int /*<<< orphan*/  crb_addr_transform (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crb_addr_transform_setup(void)
{
	crb_addr_transform(XDMA);
	crb_addr_transform(TIMR);
	crb_addr_transform(SRE);
	crb_addr_transform(SQN3);
	crb_addr_transform(SQN2);
	crb_addr_transform(SQN1);
	crb_addr_transform(SQN0);
	crb_addr_transform(SQS3);
	crb_addr_transform(SQS2);
	crb_addr_transform(SQS1);
	crb_addr_transform(SQS0);
	crb_addr_transform(RPMX7);
	crb_addr_transform(RPMX6);
	crb_addr_transform(RPMX5);
	crb_addr_transform(RPMX4);
	crb_addr_transform(RPMX3);
	crb_addr_transform(RPMX2);
	crb_addr_transform(RPMX1);
	crb_addr_transform(RPMX0);
	crb_addr_transform(ROMUSB);
	crb_addr_transform(SN);
	crb_addr_transform(QMN);
	crb_addr_transform(QMS);
	crb_addr_transform(PGNI);
	crb_addr_transform(PGND);
	crb_addr_transform(PGN3);
	crb_addr_transform(PGN2);
	crb_addr_transform(PGN1);
	crb_addr_transform(PGN0);
	crb_addr_transform(PGSI);
	crb_addr_transform(PGSD);
	crb_addr_transform(PGS3);
	crb_addr_transform(PGS2);
	crb_addr_transform(PGS1);
	crb_addr_transform(PGS0);
	crb_addr_transform(PS);
	crb_addr_transform(PH);
	crb_addr_transform(NIU);
	crb_addr_transform(I2Q);
	crb_addr_transform(EG);
	crb_addr_transform(MN);
	crb_addr_transform(MS);
	crb_addr_transform(CAS2);
	crb_addr_transform(CAS1);
	crb_addr_transform(CAS0);
	crb_addr_transform(CAM);
	crb_addr_transform(C2C1);
	crb_addr_transform(C2C0);
	crb_addr_transform(SMB);
	crb_addr_transform(OCM0);
	crb_addr_transform(I2C0);
}