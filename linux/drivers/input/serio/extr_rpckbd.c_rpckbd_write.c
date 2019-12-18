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
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMD_KARTTX ; 
 int /*<<< orphan*/  IOMD_KCTRL ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int iomd_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomd_writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpckbd_write(struct serio *port, unsigned char val)
{
	while (!(iomd_readb(IOMD_KCTRL) & (1 << 7)))
		cpu_relax();

	iomd_writeb(val, IOMD_KARTTX);

	return 0;
}