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
struct uart_sunsab_port {size_t type; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 char** sab82532_version ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static const char *sunsab_type(struct uart_port *port)
{
	struct uart_sunsab_port *up = (void *)port;
	static char buf[36];
	
	sprintf(buf, "SAB82532 %s", sab82532_version[up->type]);
	return buf;
}