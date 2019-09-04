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
 int /*<<< orphan*/  mconsole_socket_name ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int mconsole_unlink_socket(void)
{
	unlink(mconsole_socket_name);
	return 0;
}