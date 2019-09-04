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

/* Variables and functions */
 int RAVE_SP_EVNT_BASE ; 

__attribute__((used)) static bool rave_sp_id_is_event(u8 code)
{
	return (code & 0xF0) == RAVE_SP_EVNT_BASE;
}