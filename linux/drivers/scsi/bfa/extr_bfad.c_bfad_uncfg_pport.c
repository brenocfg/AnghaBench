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
struct TYPE_2__ {int roles; int /*<<< orphan*/  im_port; } ;
struct bfad_s {int /*<<< orphan*/  bfad_flags; TYPE_1__ pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_CFG_PPORT_DONE ; 
 int BFA_LPORT_ROLE_FCP_IM ; 
 int /*<<< orphan*/  bfad_im_port_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_im_scsi_host_free (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int supported_fc4s ; 

void
bfad_uncfg_pport(struct bfad_s *bfad)
{
	if ((supported_fc4s & BFA_LPORT_ROLE_FCP_IM) &&
	    (bfad->pport.roles & BFA_LPORT_ROLE_FCP_IM)) {
		bfad_im_scsi_host_free(bfad, bfad->pport.im_port);
		bfad_im_port_clean(bfad->pport.im_port);
		kfree(bfad->pport.im_port);
		bfad->pport.roles &= ~BFA_LPORT_ROLE_FCP_IM;
	}

	bfad->bfad_flags &= ~BFAD_CFG_PPORT_DONE;
}