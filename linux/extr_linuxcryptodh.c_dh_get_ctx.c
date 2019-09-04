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
struct dh_ctx {int dummy; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 struct dh_ctx* kpp_tfm_ctx (struct crypto_kpp*) ; 

__attribute__((used)) static inline struct dh_ctx *dh_get_ctx(struct crypto_kpp *tfm)
{
	return kpp_tfm_ctx(tfm);
}