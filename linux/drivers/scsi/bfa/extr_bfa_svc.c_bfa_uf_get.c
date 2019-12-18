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
struct bfa_uf_s {int dummy; } ;
struct bfa_uf_mod_s {int /*<<< orphan*/  uf_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_uf_s**) ; 

__attribute__((used)) static struct bfa_uf_s *
bfa_uf_get(struct bfa_uf_mod_s *uf_mod)
{
	struct bfa_uf_s   *uf;

	bfa_q_deq(&uf_mod->uf_free_q, &uf);
	return uf;
}