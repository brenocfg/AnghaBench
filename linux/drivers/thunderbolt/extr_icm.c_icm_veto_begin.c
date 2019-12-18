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
struct tb {int /*<<< orphan*/  dev; } ;
struct icm {int veto; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ *) ; 
 struct icm* tb_priv (struct tb*) ; 

__attribute__((used)) static void icm_veto_begin(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);

	if (!icm->veto) {
		icm->veto = true;
		/* Keep the domain powered while veto is in effect */
		pm_runtime_get(&tb->dev);
	}
}