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
typedef  size_t VCHIQ_CONNSTATE_T ;

/* Variables and functions */
 char const** conn_state_names ; 

inline const char *
get_conn_state_name(VCHIQ_CONNSTATE_T conn_state)
{
	return conn_state_names[conn_state];
}