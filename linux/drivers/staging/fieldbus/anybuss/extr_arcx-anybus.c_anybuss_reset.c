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
struct controller_priv {scalar_t__ common_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPLD_CONTROL_CRST ; 
 int /*<<< orphan*/  CPLD_CONTROL_RST1 ; 
 int /*<<< orphan*/  CPLD_CONTROL_RST2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  do_reset (struct controller_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int anybuss_reset(struct controller_priv *cd,
			 unsigned long id, bool reset)
{
	if (id >= 2)
		return -EINVAL;
	if (cd->common_reset)
		do_reset(cd, CPLD_CONTROL_CRST, reset);
	else
		do_reset(cd, id ? CPLD_CONTROL_RST2 : CPLD_CONTROL_RST1, reset);
	return 0;
}