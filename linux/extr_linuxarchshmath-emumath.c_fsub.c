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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARITH_X ; 
 int /*<<< orphan*/  BOTH_PRmn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUB ; 

__attribute__((used)) static int
fsub(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m, int n)
{
	BOTH_PRmn(ARITH_X, SUB);
	return 0;
}