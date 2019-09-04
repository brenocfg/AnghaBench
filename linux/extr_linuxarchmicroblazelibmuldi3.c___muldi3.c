#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long high; scalar_t__ low; } ;
struct TYPE_4__ {long long ll; TYPE_1__ s; } ;
typedef  TYPE_2__ DWunion ;

/* Variables and functions */
 long long __umulsidi3 (scalar_t__,scalar_t__) ; 

long long __muldi3(long long u, long long v)
{
	const DWunion uu = {.ll = u};
	const DWunion vv = {.ll = v};
	DWunion w = {.ll = __umulsidi3(uu.s.low, vv.s.low)};

	w.s.high += ((unsigned long) uu.s.low * (unsigned long) vv.s.high
		+ (unsigned long) uu.s.high * (unsigned long) vv.s.low);

	return w.ll;
}