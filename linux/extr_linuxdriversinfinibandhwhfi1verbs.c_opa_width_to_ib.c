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
typedef  int u16 ;

/* Variables and functions */
 int IB_WIDTH_1X ; 
 int IB_WIDTH_4X ; 
#define  OPA_LINK_WIDTH_1X 131 
#define  OPA_LINK_WIDTH_2X 130 
#define  OPA_LINK_WIDTH_3X 129 
#define  OPA_LINK_WIDTH_4X 128 

__attribute__((used)) static inline u16 opa_width_to_ib(u16 in)
{
	switch (in) {
	case OPA_LINK_WIDTH_1X:
	/* map 2x and 3x to 1x as they don't exist in IB */
	case OPA_LINK_WIDTH_2X:
	case OPA_LINK_WIDTH_3X:
		return IB_WIDTH_1X;
	default: /* link down or unknown, return our largest width */
	case OPA_LINK_WIDTH_4X:
		return IB_WIDTH_4X;
	}
}