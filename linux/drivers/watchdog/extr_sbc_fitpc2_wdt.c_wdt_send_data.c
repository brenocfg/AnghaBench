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
 int /*<<< orphan*/  COMMAND_PORT ; 
 int /*<<< orphan*/  DATA_PORT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_send_data(unsigned char command, unsigned char data)
{
	outb(data, DATA_PORT);
	msleep(200);
	outb(command, COMMAND_PORT);
	msleep(100);
}