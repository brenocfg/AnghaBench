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
 int BIT (int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 

const char *ucsi_cci_str(u32 cci)
{
	if (cci & GENMASK(7, 0)) {
		if (cci & BIT(29))
			return "Event pending (ACK completed)";
		if (cci & BIT(31))
			return "Event pending (command completed)";
		return "Connector Change";
	}
	if (cci & BIT(29))
		return "ACK completed";
	if (cci & BIT(31))
		return "Command completed";

	return "";
}