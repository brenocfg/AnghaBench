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
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int gb_connection_cport_shutdown (struct gb_connection*,int) ; 

__attribute__((used)) static int
gb_connection_cport_shutdown_phase_2(struct gb_connection *connection)
{
	return gb_connection_cport_shutdown(connection, 2);
}