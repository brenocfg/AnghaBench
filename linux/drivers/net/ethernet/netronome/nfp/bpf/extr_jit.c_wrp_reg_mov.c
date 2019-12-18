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
typedef  int /*<<< orphan*/  u16 ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_both (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wrp_reg_mov(struct nfp_prog *nfp_prog, u16 dst, u16 src)
{
	wrp_mov(nfp_prog, reg_both(dst), reg_b(src));
}