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
typedef  scalar_t__ u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int ahd_inb (struct ahd_softc*,scalar_t__) ; 

uint16_t
ahd_inw(struct ahd_softc *ahd, u_int port)
{
	/*
	 * Read high byte first as some registers increment
	 * or have other side effects when the low byte is
	 * read.
	 */
	uint16_t r = ahd_inb(ahd, port+1) << 8;
	return r | ahd_inb(ahd, port);
}