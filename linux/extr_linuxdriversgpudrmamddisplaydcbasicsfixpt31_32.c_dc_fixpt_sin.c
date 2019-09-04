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
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 struct fixed31_32 dc_fixpt_mul (struct fixed31_32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_sinc (struct fixed31_32) ; 

struct fixed31_32 dc_fixpt_sin(struct fixed31_32 arg)
{
	return dc_fixpt_mul(
		arg,
		dc_fixpt_sinc(arg));
}