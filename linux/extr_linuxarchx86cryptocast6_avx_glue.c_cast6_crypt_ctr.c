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
typedef  int /*<<< orphan*/  u128 ;
typedef  int /*<<< orphan*/  le128 ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int /*<<< orphan*/  __cast6_encrypt (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le128_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le128_to_be128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cast6_crypt_ctr(void *ctx, u128 *dst, const u128 *src, le128 *iv)
{
	be128 ctrblk;

	le128_to_be128(&ctrblk, iv);
	le128_inc(iv);

	__cast6_encrypt(ctx, (u8 *)&ctrblk, (u8 *)&ctrblk);
	u128_xor(dst, src, (u128 *)&ctrblk);
}