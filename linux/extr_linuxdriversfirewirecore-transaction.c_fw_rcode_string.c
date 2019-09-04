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

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
#define  RCODE_ADDRESS_ERROR 137 
#define  RCODE_BUSY 136 
#define  RCODE_CANCELLED 135 
#define  RCODE_COMPLETE 134 
#define  RCODE_CONFLICT_ERROR 133 
#define  RCODE_DATA_ERROR 132 
#define  RCODE_GENERATION 131 
#define  RCODE_NO_ACK 130 
#define  RCODE_SEND_ERROR 129 
#define  RCODE_TYPE_ERROR 128 

const char *fw_rcode_string(int rcode)
{
	static const char *const names[] = {
		[RCODE_COMPLETE]       = "no error",
		[RCODE_CONFLICT_ERROR] = "conflict error",
		[RCODE_DATA_ERROR]     = "data error",
		[RCODE_TYPE_ERROR]     = "type error",
		[RCODE_ADDRESS_ERROR]  = "address error",
		[RCODE_SEND_ERROR]     = "send error",
		[RCODE_CANCELLED]      = "timeout",
		[RCODE_BUSY]           = "busy",
		[RCODE_GENERATION]     = "bus reset",
		[RCODE_NO_ACK]         = "no ack",
	};

	if ((unsigned int)rcode < ARRAY_SIZE(names) && names[rcode])
		return names[rcode];
	else
		return "unknown";
}