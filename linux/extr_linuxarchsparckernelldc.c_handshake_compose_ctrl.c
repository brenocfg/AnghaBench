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
typedef  void* u8 ;
struct TYPE_2__ {int /*<<< orphan*/  u_data; } ;
struct ldc_packet {TYPE_1__ u; void* ctrl; void* stype; int /*<<< orphan*/  type; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDC_CTRL ; 
 struct ldc_packet* handshake_get_tx_packet (struct ldc_channel*,unsigned long*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct ldc_packet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ldc_packet *handshake_compose_ctrl(struct ldc_channel *lp,
						 u8 stype, u8 ctrl,
						 void *data, int dlen,
						 unsigned long *new_tail)
{
	struct ldc_packet *p = handshake_get_tx_packet(lp, new_tail);

	if (p) {
		memset(p, 0, sizeof(*p));
		p->type = LDC_CTRL;
		p->stype = stype;
		p->ctrl = ctrl;
		if (data)
			memcpy(p->u.u_data, data, dlen);
	}
	return p;
}