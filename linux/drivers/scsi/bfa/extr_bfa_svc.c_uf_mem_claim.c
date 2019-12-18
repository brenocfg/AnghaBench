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
struct bfa_uf_mod_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  claim_uf_post_msgs (struct bfa_uf_mod_s*) ; 
 int /*<<< orphan*/  claim_ufs (struct bfa_uf_mod_s*) ; 

__attribute__((used)) static void
uf_mem_claim(struct bfa_uf_mod_s *ufm)
{
	claim_ufs(ufm);
	claim_uf_post_msgs(ufm);
}