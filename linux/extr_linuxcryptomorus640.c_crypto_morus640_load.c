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
struct morus640_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ MORUS640_ALIGNED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus640_load_a (struct morus640_block*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_morus640_load_u (struct morus640_block*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void crypto_morus640_load(struct morus640_block *dst, const u8 *src)
{
	if (MORUS640_ALIGNED(src))
		crypto_morus640_load_a(dst, src);
	else
		crypto_morus640_load_u(dst, src);
}