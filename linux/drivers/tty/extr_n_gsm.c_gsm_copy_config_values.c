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
struct gsm_mux {scalar_t__ ftype; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mru; int /*<<< orphan*/  n2; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; int /*<<< orphan*/  initiator; int /*<<< orphan*/  encoding; int /*<<< orphan*/  adaption; } ;
struct gsm_config {int i; scalar_t__ k; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mru; int /*<<< orphan*/  n2; scalar_t__ t3; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; int /*<<< orphan*/  initiator; int /*<<< orphan*/  encapsulation; int /*<<< orphan*/  adaption; } ;

/* Variables and functions */
 scalar_t__ UIH ; 
 int /*<<< orphan*/  memset (struct gsm_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int) ; 

__attribute__((used)) static void gsm_copy_config_values(struct gsm_mux *gsm,
				   struct gsm_config *c)
{
	memset(c, 0, sizeof(*c));
	c->adaption = gsm->adaption;
	c->encapsulation = gsm->encoding;
	c->initiator = gsm->initiator;
	c->t1 = gsm->t1;
	c->t2 = gsm->t2;
	c->t3 = 0;	/* Not supported */
	c->n2 = gsm->n2;
	if (gsm->ftype == UIH)
		c->i = 1;
	else
		c->i = 2;
	pr_debug("Ftype %d i %d\n", gsm->ftype, c->i);
	c->mru = gsm->mru;
	c->mtu = gsm->mtu;
	c->k = 0;
}