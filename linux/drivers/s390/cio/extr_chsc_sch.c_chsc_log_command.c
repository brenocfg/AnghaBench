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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  dbf ;

/* Variables and functions */
 int /*<<< orphan*/  CHSC_LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CHSC_LOG_HEX (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void chsc_log_command(void *chsc_area)
{
	char dbf[10];

	snprintf(dbf, sizeof(dbf), "CHSC:%x", ((uint16_t *)chsc_area)[1]);
	CHSC_LOG(0, dbf);
	CHSC_LOG_HEX(0, chsc_area, 32);
}