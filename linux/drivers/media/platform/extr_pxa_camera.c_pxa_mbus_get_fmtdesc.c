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
typedef  int /*<<< orphan*/  u32 ;
struct pxa_mbus_pixelfmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbus_fmt ; 
 struct pxa_mbus_pixelfmt const* pxa_mbus_find_fmtdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct pxa_mbus_pixelfmt *pxa_mbus_get_fmtdesc(
	u32 code)
{
	return pxa_mbus_find_fmtdesc(code, mbus_fmt, ARRAY_SIZE(mbus_fmt));
}