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
struct sh_fpu_soft_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  DRn ; 
 int /*<<< orphan*/  FPUL ; 
 int /*<<< orphan*/  FP_CONV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_DECL_EX ; 
 int /*<<< orphan*/  FP_DECL_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Fn ; 
 int /*<<< orphan*/  Fr ; 
 int /*<<< orphan*/  PACK_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  UNPACK_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fcnvds(struct sh_fpu_soft_struct *fregs, int n)
{
	FP_DECL_EX;
	FP_DECL_D(Fn);
	FP_DECL_S(Fr);
	UNPACK_D(Fn, DRn);
	FP_CONV(S, D, 1, 2, Fr, Fn);
	PACK_S(FPUL, Fr);
	return 0;
}