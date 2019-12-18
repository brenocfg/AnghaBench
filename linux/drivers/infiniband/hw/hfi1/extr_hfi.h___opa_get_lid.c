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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MULTICAST_LID_BASE ; 
 int /*<<< orphan*/  OPA_MCAST_NR ; 
#define  OPA_PORT_PACKET_FORMAT_10B 131 
#define  OPA_PORT_PACKET_FORMAT_16B 130 
#define  OPA_PORT_PACKET_FORMAT_8B 129 
#define  OPA_PORT_PACKET_FORMAT_9B 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int hfi1_check_mcast (int) ; 
 int opa_get_mcast_base (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 __opa_get_lid(u32 lid, u8 format)
{
	bool is_mcast = hfi1_check_mcast(lid);

	switch (format) {
	case OPA_PORT_PACKET_FORMAT_8B:
	case OPA_PORT_PACKET_FORMAT_10B:
		if (is_mcast)
			return (lid - opa_get_mcast_base(OPA_MCAST_NR) +
				0xF0000);
		return lid & 0xFFFFF;
	case OPA_PORT_PACKET_FORMAT_16B:
		if (is_mcast)
			return (lid - opa_get_mcast_base(OPA_MCAST_NR) +
				0xF00000);
		return lid & 0xFFFFFF;
	case OPA_PORT_PACKET_FORMAT_9B:
		if (is_mcast)
			return (lid -
				opa_get_mcast_base(OPA_MCAST_NR) +
				be16_to_cpu(IB_MULTICAST_LID_BASE));
		else
			return lid & 0xFFFF;
	default:
		return lid;
	}
}