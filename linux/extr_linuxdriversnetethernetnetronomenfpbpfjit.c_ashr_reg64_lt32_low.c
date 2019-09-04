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
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 void shr_reg64_lt32_low (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ashr_reg64_lt32_low(struct nfp_prog *nfp_prog, u8 dst, u8 src)
{
	/* NOTE: it is the same as logic shift because we don't need to shift in
	 * signedness bit when the shift amount is less than 32.
	 */
	return shr_reg64_lt32_low(nfp_prog, dst, src);
}