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
struct niu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NIU_LDG_MAX ; 
 int NIU_LDG_MIN ; 
 int /*<<< orphan*/  SID (int) ; 
 int SID_FUNC_SHIFT ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_set_ldg_sid(struct niu *np, int ldg, int func, int vector)
{
	if ((ldg < NIU_LDG_MIN || ldg > NIU_LDG_MAX) ||
	    (func < 0 || func > 3) ||
	    (vector < 0 || vector > 0x1f))
		return -EINVAL;

	nw64(SID(ldg), (func << SID_FUNC_SHIFT) | vector);

	return 0;
}