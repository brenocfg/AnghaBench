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
struct vio_driver_state {int dr_state; int /*<<< orphan*/  hs_state; struct vio_dring_state* drings; } ;
struct vio_dring_state {scalar_t__ ident; } ;
struct vio_dring_register {scalar_t__ dring_ident; int /*<<< orphan*/  num_cookies; int /*<<< orphan*/  options; int /*<<< orphan*/  descr_size; int /*<<< orphan*/  num_descr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 size_t VIO_DRIVER_TX_RING ; 
 int VIO_DR_STATE_TXREG ; 
 int VIO_DR_STATE_TXREQ ; 
 int /*<<< orphan*/  VIO_HS_SENT_RDX ; 
 scalar_t__ all_drings_registered (struct vio_driver_state*) ; 
 int handshake_failure (struct vio_driver_state*) ; 
 scalar_t__ send_rdx (struct vio_driver_state*) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_dreg_ack(struct vio_driver_state *vio,
			    struct vio_dring_register *pkt)
{
	struct vio_dring_state *dr;

	viodbg(HS, "GOT DRING_REG ACK ident[%llx] "
	       "ndesc[%u] dsz[%u] opt[0x%x] ncookies[%u]\n",
	       (unsigned long long) pkt->dring_ident,
	       pkt->num_descr, pkt->descr_size, pkt->options,
	       pkt->num_cookies);

	dr = &vio->drings[VIO_DRIVER_TX_RING];

	if (!(vio->dr_state & VIO_DR_STATE_TXREQ))
		return handshake_failure(vio);

	dr->ident = pkt->dring_ident;
	vio->dr_state |= VIO_DR_STATE_TXREG;

	if (all_drings_registered(vio)) {
		if (send_rdx(vio) < 0)
			return handshake_failure(vio);
		vio->hs_state = VIO_HS_SENT_RDX;
	}
	return 0;
}