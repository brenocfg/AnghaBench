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

/* Variables and functions */
 int /*<<< orphan*/  __crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbc_paes_alg ; 
 int /*<<< orphan*/  ctr_paes_alg ; 
 scalar_t__ ctrblk ; 
 int /*<<< orphan*/  ecb_paes_alg ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  xts_paes_alg ; 

__attribute__((used)) static void paes_s390_fini(void)
{
	if (ctrblk)
		free_page((unsigned long) ctrblk);
	__crypto_unregister_alg(&ctr_paes_alg);
	__crypto_unregister_alg(&xts_paes_alg);
	__crypto_unregister_alg(&cbc_paes_alg);
	__crypto_unregister_alg(&ecb_paes_alg);
}