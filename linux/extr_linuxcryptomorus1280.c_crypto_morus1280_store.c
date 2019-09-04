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
typedef  int /*<<< orphan*/  u8 ;
struct morus1280_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ MORUS1280_ALIGNED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_morus1280_store_a (int /*<<< orphan*/ *,struct morus1280_block const*) ; 
 int /*<<< orphan*/  crypto_morus1280_store_u (int /*<<< orphan*/ *,struct morus1280_block const*) ; 

__attribute__((used)) static void crypto_morus1280_store(u8 *dst, const struct morus1280_block *src)
{
	if (MORUS1280_ALIGNED(dst))
		crypto_morus1280_store_a(dst, src);
	else
		crypto_morus1280_store_u(dst, src);
}