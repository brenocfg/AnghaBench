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

/* Variables and functions */
 int /*<<< orphan*/  CONST_L2T ; 
 int RC_UP ; 
 int /*<<< orphan*/  TAG_Valid ; 
 int /*<<< orphan*/  fld_const (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fldl2t(int rc)
{
	fld_const(&CONST_L2T, (rc == RC_UP) ? 1 : 0, TAG_Valid);
}