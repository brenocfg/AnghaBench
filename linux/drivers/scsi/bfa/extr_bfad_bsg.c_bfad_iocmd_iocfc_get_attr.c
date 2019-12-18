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
struct bfad_s {int /*<<< orphan*/  bfa; } ;
struct bfa_bsg_iocfc_attr_s {int /*<<< orphan*/  iocfc_attr; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_iocfc_get_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
bfad_iocmd_iocfc_get_attr(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_iocfc_attr_s *iocmd = (struct bfa_bsg_iocfc_attr_s *)cmd;

	iocmd->status = BFA_STATUS_OK;
	bfa_iocfc_get_attr(&bfad->bfa, &iocmd->iocfc_attr);

	return 0;
}