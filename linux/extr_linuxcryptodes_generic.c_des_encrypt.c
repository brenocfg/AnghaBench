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
typedef  int /*<<< orphan*/  u32 ;
struct des_ctx {int /*<<< orphan*/ * expkey; } ;
struct crypto_tfm {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROUND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void des_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct des_ctx *ctx = crypto_tfm_ctx(tfm);
	const u32 *K = ctx->expkey;
	const __le32 *s = (const __le32 *)src;
	__le32 *d = (__le32 *)dst;
	u32 L, R, A, B;
	int i;

	L = le32_to_cpu(s[0]);
	R = le32_to_cpu(s[1]);

	IP(L, R, A);
	for (i = 0; i < 8; i++) {
		ROUND(L, R, A, B, K, 2);
		ROUND(R, L, A, B, K, 2);
	}
	FP(R, L, A);

	d[0] = cpu_to_le32(R);
	d[1] = cpu_to_le32(L);
}