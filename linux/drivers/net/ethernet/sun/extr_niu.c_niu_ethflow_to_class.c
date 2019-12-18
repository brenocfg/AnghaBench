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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 139 
#define  AH_ESP_V6_FLOW 138 
#define  AH_V4_FLOW 137 
#define  AH_V6_FLOW 136 
 int /*<<< orphan*/  CLASS_CODE_AH_ESP_IPV4 ; 
 int /*<<< orphan*/  CLASS_CODE_AH_ESP_IPV6 ; 
 int /*<<< orphan*/  CLASS_CODE_SCTP_IPV4 ; 
 int /*<<< orphan*/  CLASS_CODE_SCTP_IPV6 ; 
 int /*<<< orphan*/  CLASS_CODE_TCP_IPV4 ; 
 int /*<<< orphan*/  CLASS_CODE_TCP_IPV6 ; 
 int /*<<< orphan*/  CLASS_CODE_UDP_IPV4 ; 
 int /*<<< orphan*/  CLASS_CODE_UDP_IPV6 ; 
#define  ESP_V4_FLOW 135 
#define  ESP_V6_FLOW 134 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static int niu_ethflow_to_class(int flow_type, u64 *class)
{
	switch (flow_type) {
	case TCP_V4_FLOW:
		*class = CLASS_CODE_TCP_IPV4;
		break;
	case UDP_V4_FLOW:
		*class = CLASS_CODE_UDP_IPV4;
		break;
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
		*class = CLASS_CODE_AH_ESP_IPV4;
		break;
	case SCTP_V4_FLOW:
		*class = CLASS_CODE_SCTP_IPV4;
		break;
	case TCP_V6_FLOW:
		*class = CLASS_CODE_TCP_IPV6;
		break;
	case UDP_V6_FLOW:
		*class = CLASS_CODE_UDP_IPV6;
		break;
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
		*class = CLASS_CODE_AH_ESP_IPV6;
		break;
	case SCTP_V6_FLOW:
		*class = CLASS_CODE_SCTP_IPV6;
		break;
	default:
		return 0;
	}

	return 1;
}