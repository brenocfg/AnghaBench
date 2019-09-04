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
typedef  int u32 ;

/* Variables and functions */
#define  ISDN_PROTO_L2_FAX 137 
#define  ISDN_PROTO_L2_HDLC 136 
#define  ISDN_PROTO_L2_MODEM 135 
#define  ISDN_PROTO_L2_TRANS 134 
#define  ISDN_PROTO_L2_V11019 133 
#define  ISDN_PROTO_L2_V11038 132 
#define  ISDN_PROTO_L2_V11096 131 
#define  ISDN_PROTO_L2_X75BUI 130 
#define  ISDN_PROTO_L2_X75I 129 
#define  ISDN_PROTO_L2_X75UI 128 

__attribute__((used)) static inline u32 b1prot(int l2, int l3)
{
	switch (l2) {
	case ISDN_PROTO_L2_X75I:
	case ISDN_PROTO_L2_X75UI:
	case ISDN_PROTO_L2_X75BUI:
		return 0;
	case ISDN_PROTO_L2_HDLC:
	default:
		return 0;
	case ISDN_PROTO_L2_TRANS:
		return 1;
	case ISDN_PROTO_L2_V11096:
	case ISDN_PROTO_L2_V11019:
	case ISDN_PROTO_L2_V11038:
		return 2;
	case ISDN_PROTO_L2_FAX:
		return 4;
	case ISDN_PROTO_L2_MODEM:
		return 8;
	}
}