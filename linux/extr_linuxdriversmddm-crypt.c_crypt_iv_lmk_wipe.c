#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iv_lmk_private {scalar_t__ seed; } ;
struct TYPE_2__ {struct iv_lmk_private lmk; } ;
struct crypt_config {TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  LMK_SEED_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_iv_lmk_wipe(struct crypt_config *cc)
{
	struct iv_lmk_private *lmk = &cc->iv_gen_private.lmk;

	if (lmk->seed)
		memset(lmk->seed, 0, LMK_SEED_SIZE);

	return 0;
}