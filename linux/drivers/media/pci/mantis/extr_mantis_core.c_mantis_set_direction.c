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
struct mantis_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int mmread (int) ; 
 int /*<<< orphan*/  mmwrite (int,int) ; 
 int /*<<< orphan*/  verbose ; 

void mantis_set_direction(struct mantis_pci *mantis, int direction)
{
	u32 reg;

	reg = mmread(0x28);
	dprintk(verbose, MANTIS_DEBUG, 1, "TS direction setup");
	if (direction == 0x01) {
		/* to CI */
		reg |= 0x04;
		mmwrite(reg, 0x28);
		reg &= 0xff - 0x04;
		mmwrite(reg, 0x28);
	} else {
		reg &= 0xff - 0x04;
		mmwrite(reg, 0x28);
		reg |= 0x04;
		mmwrite(reg, 0x28);
	}
}