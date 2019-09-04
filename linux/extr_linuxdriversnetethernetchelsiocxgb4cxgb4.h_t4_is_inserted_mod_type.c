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
 unsigned int FW_PORT_MOD_TYPE_ERROR ; 
 unsigned int FW_PORT_MOD_TYPE_NONE ; 
 unsigned int FW_PORT_MOD_TYPE_NOTSUPPORTED ; 
 unsigned int FW_PORT_MOD_TYPE_UNKNOWN ; 

__attribute__((used)) static inline bool t4_is_inserted_mod_type(unsigned int fw_mod_type)
{
	return (fw_mod_type != FW_PORT_MOD_TYPE_NONE &&
		fw_mod_type != FW_PORT_MOD_TYPE_NOTSUPPORTED &&
		fw_mod_type != FW_PORT_MOD_TYPE_UNKNOWN &&
		fw_mod_type != FW_PORT_MOD_TYPE_ERROR);
}