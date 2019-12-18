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
typedef  enum mcu_msg_type { ____Placeholder_mcu_msg_type } mcu_msg_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  MCU_MSG_TYPE_CREATE_CHANNEL 134 
#define  MCU_MSG_TYPE_DESTROY_CHANNEL 133 
#define  MCU_MSG_TYPE_ENCODE_FRAME 132 
#define  MCU_MSG_TYPE_INIT 131 
#define  MCU_MSG_TYPE_PUSH_BUFFER_INTERMEDIATE 130 
#define  MCU_MSG_TYPE_PUSH_BUFFER_REFERENCE 129 
#define  MCU_MSG_TYPE_PUT_STREAM_BUFFER 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *msg_type_name(enum mcu_msg_type type)
{
	static char buf[9];

	switch (type) {
	case MCU_MSG_TYPE_INIT:
		return "INIT";
	case MCU_MSG_TYPE_CREATE_CHANNEL:
		return "CREATE_CHANNEL";
	case MCU_MSG_TYPE_DESTROY_CHANNEL:
		return "DESTROY_CHANNEL";
	case MCU_MSG_TYPE_ENCODE_FRAME:
		return "ENCODE_FRAME";
	case MCU_MSG_TYPE_PUT_STREAM_BUFFER:
		return "PUT_STREAM_BUFFER";
	case MCU_MSG_TYPE_PUSH_BUFFER_INTERMEDIATE:
		return "PUSH_BUFFER_INTERMEDIATE";
	case MCU_MSG_TYPE_PUSH_BUFFER_REFERENCE:
		return "PUSH_BUFFER_REFERENCE";
	default:
		snprintf(buf, sizeof(buf), "(0x%04x)", type);
		return buf;
	}
}