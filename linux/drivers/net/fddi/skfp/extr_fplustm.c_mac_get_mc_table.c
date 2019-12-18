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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {struct s_fpmc* table; } ;
struct TYPE_5__ {TYPE_1__ mc; } ;
struct TYPE_6__ {TYPE_2__ fp; } ;
struct s_smc {TYPE_3__ hw; } ;
struct s_fpmc {int /*<<< orphan*/  a; int /*<<< orphan*/  n; } ;
struct fddi_addr {int /*<<< orphan*/ * a; } ;

/* Variables and functions */
 int FPMAX_MULTICAST ; 
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (char*,char*) ; 

__attribute__((used)) static struct s_fpmc* mac_get_mc_table(struct s_smc *smc,
				       struct fddi_addr *user,
				       struct fddi_addr *own,
				       int del, int can)
{
	struct s_fpmc	*tb ;
	struct s_fpmc	*slot ;
	u_char	*p ;
	int i ;

	/*
	 * set own = can(user)
	 */
	*own = *user ;
	if (can) {
		p = own->a ;
		for (i = 0 ; i < 6 ; i++, p++)
			*p = bitrev8(*p);
	}
	slot = NULL;
	for (i = 0, tb = smc->hw.fp.mc.table ; i < FPMAX_MULTICAST ; i++, tb++){
		if (!tb->n) {		/* not used */
			if (!del && !slot)	/* if !del save first free */
				slot = tb ;
			continue ;
		}
		if (!ether_addr_equal((char *)&tb->a, (char *)own))
			continue ;
		return tb;
	}
	return slot;			/* return first free or NULL */
}