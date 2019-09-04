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
struct ldc_version {int dummy; } ;
struct TYPE_2__ {scalar_t__ u_data; } ;
struct ldc_packet {int stype; TYPE_1__ u; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int LDC_ABORT (struct ldc_channel*) ; 
#define  LDC_ACK 130 
#define  LDC_INFO 129 
#define  LDC_NACK 128 
 int process_ver_ack (struct ldc_channel*,struct ldc_version*) ; 
 int process_ver_info (struct ldc_channel*,struct ldc_version*) ; 
 int process_ver_nack (struct ldc_channel*,struct ldc_version*) ; 

__attribute__((used)) static int process_version(struct ldc_channel *lp,
			   struct ldc_packet *p)
{
	struct ldc_version *vp;

	vp = (struct ldc_version *) p->u.u_data;

	switch (p->stype) {
	case LDC_INFO:
		return process_ver_info(lp, vp);

	case LDC_ACK:
		return process_ver_ack(lp, vp);

	case LDC_NACK:
		return process_ver_nack(lp, vp);

	default:
		return LDC_ABORT(lp);
	}
}