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
typedef  union ieee754dp {int dummy; } ieee754dp ;

/* Variables and functions */
 union ieee754dp _dp_maddf (union ieee754dp,union ieee754dp,union ieee754dp,int /*<<< orphan*/ ) ; 

union ieee754dp ieee754dp_maddf(union ieee754dp z, union ieee754dp x,
				union ieee754dp y)
{
	return _dp_maddf(z, x, y, 0);
}