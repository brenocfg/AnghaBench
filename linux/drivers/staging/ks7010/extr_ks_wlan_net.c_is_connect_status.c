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
 int CONNECT_STATUS ; 
 int CONNECT_STATUS_MASK ; 

bool is_connect_status(u32 status)
{
	return (status & CONNECT_STATUS_MASK) == CONNECT_STATUS;
}