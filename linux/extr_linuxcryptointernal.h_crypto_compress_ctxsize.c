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
struct crypto_alg {unsigned int cra_ctxsize; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int crypto_compress_ctxsize(struct crypto_alg *alg)
{
	return alg->cra_ctxsize;
}