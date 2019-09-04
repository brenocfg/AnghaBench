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
 int const FPSCR_FR ; 
 int const FPSCR_PR ; 
 int const FPSCR_SZ ; 
 int /*<<< orphan*/  fsca (struct sh_fpu_soft_struct*,int) ; 
 int /*<<< orphan*/  ftrv (struct sh_fpu_soft_struct*,int) ; 
 int /*<<< orphan*/  fxchg (struct sh_fpu_soft_struct*,int const) ; 

__attribute__((used)) static int id_fxfd(struct sh_fpu_soft_struct *fregs, int x)
{
	const int flag[] = { FPSCR_SZ, FPSCR_PR, FPSCR_FR, 0 };
	switch (x & 3) {
	case 3:
		fxchg(fregs, flag[x >> 2]);
		break;
	case 1:
		ftrv(fregs, x - 1);
		break;
	default:
		fsca(fregs, x);
	}
	return 0;
}