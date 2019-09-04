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
typedef  union ieee754sp {int dummy; } ieee754sp ;

/* Variables and functions */
 int /*<<< orphan*/  COMPXSP ; 
 int /*<<< orphan*/  EXPLODEXSP ; 
 int xc ; 

int ieee754sp_class(union ieee754sp x)
{
	COMPXSP;
	EXPLODEXSP;
	return xc;
}