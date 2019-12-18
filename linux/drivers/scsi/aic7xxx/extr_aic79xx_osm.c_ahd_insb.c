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
typedef  int /*<<< orphan*/  uint8_t ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahd_inb (struct ahd_softc*,long) ; 

void
ahd_insb(struct ahd_softc * ahd, long port, uint8_t *array, int count)
{
	int i;

	/*
	 * There is probably a more efficient way to do this on Linux
	 * but we don't use this for anything speed critical and this
	 * should work.
	 */
	for (i = 0; i < count; i++)
		*array++ = ahd_inb(ahd, port);
}