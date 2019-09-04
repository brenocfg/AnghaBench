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
struct TYPE_2__ {int stype; } ;
struct vio_ver_info {TYPE_1__ tag; } ;
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
#define  VIO_SUBTYPE_ACK 130 
#define  VIO_SUBTYPE_INFO 129 
#define  VIO_SUBTYPE_NACK 128 
 int handshake_failure (struct vio_driver_state*) ; 
 int process_ver_ack (struct vio_driver_state*,struct vio_ver_info*) ; 
 int process_ver_info (struct vio_driver_state*,struct vio_ver_info*) ; 
 int process_ver_nack (struct vio_driver_state*,struct vio_ver_info*) ; 

__attribute__((used)) static int process_ver(struct vio_driver_state *vio, struct vio_ver_info *pkt)
{
	switch (pkt->tag.stype) {
	case VIO_SUBTYPE_INFO:
		return process_ver_info(vio, pkt);

	case VIO_SUBTYPE_ACK:
		return process_ver_ack(vio, pkt);

	case VIO_SUBTYPE_NACK:
		return process_ver_nack(vio, pkt);

	default:
		return handshake_failure(vio);
	}
}