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
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;

/* Variables and functions */
#define  TILFMT_16BIT 131 
#define  TILFMT_32BIT 130 
#define  TILFMT_8BIT 129 
#define  TILFMT_PAGE 128 

__attribute__((used)) static inline bool validfmt(enum tiler_fmt fmt)
{
	switch (fmt) {
	case TILFMT_8BIT:
	case TILFMT_16BIT:
	case TILFMT_32BIT:
	case TILFMT_PAGE:
		return true;
	default:
		return false;
	}
}