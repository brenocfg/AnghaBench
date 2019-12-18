#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bcm3510_state {int dummy; } ;
struct TYPE_5__ {int RESYNC; int CNTCTL; int BITCNT; } ;
struct TYPE_6__ {TYPE_1__ BERCTL_fa; } ;
typedef  TYPE_2__ bcm3510_register_value ;

/* Variables and functions */
 int bcm3510_readB (struct bcm3510_state*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  bcm3510_writeB (struct bcm3510_state*,int,TYPE_2__) ; 

__attribute__((used)) static int bcm3510_bert_reset(struct bcm3510_state *st)
{
	bcm3510_register_value b;
	int ret;

	if ((ret = bcm3510_readB(st,0xfa,&b)) < 0)
		return ret;

	b.BERCTL_fa.RESYNC = 0; bcm3510_writeB(st,0xfa,b);
	b.BERCTL_fa.RESYNC = 1; bcm3510_writeB(st,0xfa,b);
	b.BERCTL_fa.RESYNC = 0; bcm3510_writeB(st,0xfa,b);
	b.BERCTL_fa.CNTCTL = 1; b.BERCTL_fa.BITCNT = 1; bcm3510_writeB(st,0xfa,b);

	/* clear residual bit counter TODO  */
	return 0;
}