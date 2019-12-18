#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tb {TYPE_1__* root_switch; int /*<<< orphan*/  dev; } ;
struct icm {int /*<<< orphan*/  (* set_uuid ) (struct tb*) ;int /*<<< orphan*/  rpm; int /*<<< orphan*/  can_upgrade_nvm; scalar_t__ safe_mode; } ;
struct TYPE_7__ {int no_nvm_upgrade; int /*<<< orphan*/  rpm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct tb*) ; 
 struct icm* tb_priv (struct tb*) ; 
 int tb_switch_add (TYPE_1__*) ; 
 TYPE_1__* tb_switch_alloc (struct tb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* tb_switch_alloc_safe_mode (struct tb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_switch_put (TYPE_1__*) ; 

__attribute__((used)) static int icm_start(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);
	int ret;

	if (icm->safe_mode)
		tb->root_switch = tb_switch_alloc_safe_mode(tb, &tb->dev, 0);
	else
		tb->root_switch = tb_switch_alloc(tb, &tb->dev, 0);
	if (IS_ERR(tb->root_switch))
		return PTR_ERR(tb->root_switch);

	tb->root_switch->no_nvm_upgrade = !icm->can_upgrade_nvm;
	tb->root_switch->rpm = icm->rpm;

	if (icm->set_uuid)
		icm->set_uuid(tb);

	ret = tb_switch_add(tb->root_switch);
	if (ret) {
		tb_switch_put(tb->root_switch);
		tb->root_switch = NULL;
	}

	return ret;
}