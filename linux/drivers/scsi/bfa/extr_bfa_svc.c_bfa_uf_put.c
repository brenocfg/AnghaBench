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
struct bfa_uf_s {int /*<<< orphan*/  qe; } ;
struct bfa_uf_mod_s {int /*<<< orphan*/  uf_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_uf_put(struct bfa_uf_mod_s *uf_mod, struct bfa_uf_s *uf)
{
	list_add_tail(&uf->qe, &uf_mod->uf_free_q);
}