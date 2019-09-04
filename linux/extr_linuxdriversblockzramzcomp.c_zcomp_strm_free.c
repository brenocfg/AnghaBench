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
struct zcomp_strm {scalar_t__ buffer; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_comp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  kfree (struct zcomp_strm*) ; 

__attribute__((used)) static void zcomp_strm_free(struct zcomp_strm *zstrm)
{
	if (!IS_ERR_OR_NULL(zstrm->tfm))
		crypto_free_comp(zstrm->tfm);
	free_pages((unsigned long)zstrm->buffer, 1);
	kfree(zstrm);
}