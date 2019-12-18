#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct link_bits   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct link_bits {int from; int to; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__ const*) ; 
#define  OPA_LINK_WIDTH_1X 131 
#define  OPA_LINK_WIDTH_2X 130 
#define  OPA_LINK_WIDTH_3X 129 
#define  OPA_LINK_WIDTH_4X 128 

__attribute__((used)) static u16 opa_to_vc_link_widths(u16 opa_widths)
{
	int i;
	u16 result = 0;

	static const struct link_bits {
		u16 from;
		u16 to;
	} opa_link_xlate[] = {
		{ OPA_LINK_WIDTH_1X, 1 << (1 - 1)  },
		{ OPA_LINK_WIDTH_2X, 1 << (2 - 1)  },
		{ OPA_LINK_WIDTH_3X, 1 << (3 - 1)  },
		{ OPA_LINK_WIDTH_4X, 1 << (4 - 1)  },
	};

	for (i = 0; i < ARRAY_SIZE(opa_link_xlate); i++) {
		if (opa_widths & opa_link_xlate[i].from)
			result |= opa_link_xlate[i].to;
	}
	return result;
}