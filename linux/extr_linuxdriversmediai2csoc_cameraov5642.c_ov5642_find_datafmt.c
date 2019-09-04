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
typedef  scalar_t__ u32 ;
struct ov5642_datafmt {scalar_t__ code; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ov5642_datafmt const*) ; 
 struct ov5642_datafmt const* ov5642_colour_fmts ; 

__attribute__((used)) static const struct ov5642_datafmt
			*ov5642_find_datafmt(u32 code)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ov5642_colour_fmts); i++)
		if (ov5642_colour_fmts[i].code == code)
			return ov5642_colour_fmts + i;

	return NULL;
}