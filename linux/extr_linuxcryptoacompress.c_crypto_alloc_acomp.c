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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_acomp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_acomp_type ; 
 struct crypto_acomp* crypto_alloc_tfm (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct crypto_acomp *crypto_alloc_acomp(const char *alg_name, u32 type,
					u32 mask)
{
	return crypto_alloc_tfm(alg_name, &crypto_acomp_type, type, mask);
}