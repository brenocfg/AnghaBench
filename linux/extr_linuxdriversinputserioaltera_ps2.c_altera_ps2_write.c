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
struct serio {struct ps2if* port_data; } ;
struct ps2if {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_ps2_write(struct serio *io, unsigned char val)
{
	struct ps2if *ps2if = io->port_data;

	writel(val, ps2if->base);
	return 0;
}