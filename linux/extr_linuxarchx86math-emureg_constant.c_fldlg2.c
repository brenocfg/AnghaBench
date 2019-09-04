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
 int /*<<< orphan*/  CONST_LG2 ; 
 scalar_t__ DOWN_OR_CHOP (int) ; 
 int /*<<< orphan*/  TAG_Valid ; 
 int /*<<< orphan*/  fld_const (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fldlg2(int rc)
{
	fld_const(&CONST_LG2, DOWN_OR_CHOP(rc) ? -1 : 0, TAG_Valid);
}