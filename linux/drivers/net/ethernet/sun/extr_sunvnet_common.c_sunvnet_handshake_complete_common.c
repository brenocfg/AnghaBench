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
struct vio_driver_state {struct vio_dring_state* drings; } ;
struct vio_dring_state {int rcv_nxt; int snd_nxt; } ;

/* Variables and functions */
 size_t VIO_DRIVER_RX_RING ; 
 size_t VIO_DRIVER_TX_RING ; 

void sunvnet_handshake_complete_common(struct vio_driver_state *vio)
{
	struct vio_dring_state *dr;

	dr = &vio->drings[VIO_DRIVER_RX_RING];
	dr->rcv_nxt = 1;
	dr->snd_nxt = 1;

	dr = &vio->drings[VIO_DRIVER_TX_RING];
	dr->rcv_nxt = 1;
	dr->snd_nxt = 1;
}