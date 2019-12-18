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
typedef  int u8 ;
typedef  enum via_clksrc { ____Placeholder_via_clksrc } via_clksrc ;

/* Variables and functions */
#define  VIA_CLKSRC_CAP0 133 
#define  VIA_CLKSRC_CAP1 132 
#define  VIA_CLKSRC_DVP1TVCLKR 131 
#define  VIA_CLKSRC_TVPLL 130 
#define  VIA_CLKSRC_TVX1 129 
#define  VIA_CLKSRC_X1 128 

__attribute__((used)) static inline u8 set_clock_source_common(enum via_clksrc source, bool use_pll)
{
	u8 data = 0;

	switch (source) {
	case VIA_CLKSRC_X1:
		data = 0x00;
		break;
	case VIA_CLKSRC_TVX1:
		data = 0x02;
		break;
	case VIA_CLKSRC_TVPLL:
		data = 0x04; /* 0x06 should be the same */
		break;
	case VIA_CLKSRC_DVP1TVCLKR:
		data = 0x0A;
		break;
	case VIA_CLKSRC_CAP0:
		data = 0xC;
		break;
	case VIA_CLKSRC_CAP1:
		data = 0x0E;
		break;
	}

	if (!use_pll)
		data |= 1;

	return data;
}