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
struct dvb_net_priv {int ule_dbit; scalar_t__ ule_bridged; scalar_t__ ule_sndu_remain; scalar_t__ ule_sndu_type_1; scalar_t__ ule_sndu_type; scalar_t__ ule_sndu_len; int /*<<< orphan*/ * ule_next_hdr; int /*<<< orphan*/ * ule_skb; } ;

/* Variables and functions */

__attribute__((used)) static inline void reset_ule( struct dvb_net_priv *p )
{
	p->ule_skb = NULL;
	p->ule_next_hdr = NULL;
	p->ule_sndu_len = 0;
	p->ule_sndu_type = 0;
	p->ule_sndu_type_1 = 0;
	p->ule_sndu_remain = 0;
	p->ule_dbit = 0xFF;
	p->ule_bridged = 0;
}