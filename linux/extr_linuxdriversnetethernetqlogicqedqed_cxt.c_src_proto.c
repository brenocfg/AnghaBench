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
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;

/* Variables and functions */
 int PROTOCOLID_FCOE ; 
 int PROTOCOLID_ISCSI ; 
 int PROTOCOLID_IWARP ; 

__attribute__((used)) static bool src_proto(enum protocol_type type)
{
	return type == PROTOCOLID_ISCSI ||
	       type == PROTOCOLID_FCOE ||
	       type == PROTOCOLID_IWARP;
}