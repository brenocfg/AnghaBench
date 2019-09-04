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
 int /*<<< orphan*/  WRITE_RWA (int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inb (int) ; 

__attribute__((used)) static inline void rwa010_global_init(void)
{
	WRITE_RWA(6, 2);	// Assign a card no = 2

	dprintk("Card no = %d\n", inb(0x203));

	/* disable the modem section of the chip */
	WRITE_RWA(7, 3);
	WRITE_RWA(0x30, 0);

	/* disable the cdrom section of the chip */
	WRITE_RWA(7, 4);
	WRITE_RWA(0x30, 0);

	/* disable the MPU-401 section of the chip */
	WRITE_RWA(7, 2);
	WRITE_RWA(0x30, 0);
}