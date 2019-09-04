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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MON_SRC_AVSB ; 
 scalar_t__ MON_SRC_VBAT ; 
 scalar_t__ MON_SRC_VCC ; 
 scalar_t__ MON_SRC_VSB ; 
 int /*<<< orphan*/  clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u16 in_to_reg(u32 val, u8 src)
{
	int scale = 16;

	if (src == MON_SRC_VCC || src == MON_SRC_VSB || src == MON_SRC_AVSB ||
	    src == MON_SRC_VBAT)
		scale <<= 1;

	return clamp_val(DIV_ROUND_CLOSEST(val, scale), 0, 127);
}