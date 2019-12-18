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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  bits; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
struct siw_cep {scalar_t__ state; int /*<<< orphan*/ * sock; TYPE_3__ mpa; } ;
struct iw_cm_id {scalar_t__ provider_data; } ;

/* Variables and functions */
 int ECONNRESET ; 
 scalar_t__ MPA_REVISION_1 ; 
 int /*<<< orphan*/  MPA_RR_FLAG_REJECT ; 
 scalar_t__ SIW_EPSTATE_CLOSED ; 
 scalar_t__ SIW_EPSTATE_RECVD_MPAREQ ; 
 scalar_t__ __mpa_rr_revision (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_cancel_mpatimer (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_put (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_free (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_inuse (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,...) ; 
 int /*<<< orphan*/  siw_send_mpareqrep (struct siw_cep*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_socket_disassoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 

int siw_reject(struct iw_cm_id *id, const void *pdata, u8 pd_len)
{
	struct siw_cep *cep = (struct siw_cep *)id->provider_data;

	siw_cep_set_inuse(cep);
	siw_cep_put(cep);

	siw_cancel_mpatimer(cep);

	if (cep->state != SIW_EPSTATE_RECVD_MPAREQ) {
		siw_dbg_cep(cep, "out of state\n");

		siw_cep_set_free(cep);
		siw_cep_put(cep); /* put last reference */

		return -ECONNRESET;
	}
	siw_dbg_cep(cep, "cep->state %d, pd_len %d\n", cep->state,
		    pd_len);

	if (__mpa_rr_revision(cep->mpa.hdr.params.bits) >= MPA_REVISION_1) {
		cep->mpa.hdr.params.bits |= MPA_RR_FLAG_REJECT; /* reject */
		siw_send_mpareqrep(cep, pdata, pd_len);
	}
	siw_socket_disassoc(cep->sock);
	sock_release(cep->sock);
	cep->sock = NULL;

	cep->state = SIW_EPSTATE_CLOSED;

	siw_cep_set_free(cep);
	siw_cep_put(cep);

	return 0;
}