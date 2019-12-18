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
struct tb_nhi {int dummy; } ;
struct tb_cm {int /*<<< orphan*/  tunnel_list; } ;
struct tb {int /*<<< orphan*/ * cm_ops; int /*<<< orphan*/  security_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TB_SECURITY_USER ; 
 int /*<<< orphan*/  tb_cm_ops ; 
 struct tb* tb_domain_alloc (struct tb_nhi*,int) ; 
 struct tb_cm* tb_priv (struct tb*) ; 
 int /*<<< orphan*/  x86_apple_machine ; 

struct tb *tb_probe(struct tb_nhi *nhi)
{
	struct tb_cm *tcm;
	struct tb *tb;

	if (!x86_apple_machine)
		return NULL;

	tb = tb_domain_alloc(nhi, sizeof(*tcm));
	if (!tb)
		return NULL;

	tb->security_level = TB_SECURITY_USER;
	tb->cm_ops = &tb_cm_ops;

	tcm = tb_priv(tb);
	INIT_LIST_HEAD(&tcm->tunnel_list);

	return tb;
}