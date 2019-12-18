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
typedef  int uint64_t ;
typedef  scalar_t__ u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int ahd_inb (struct ahd_softc*,scalar_t__) ; 

uint64_t
ahd_inq(struct ahd_softc *ahd, u_int port)
{
	return ((ahd_inb(ahd, port))
	      | (ahd_inb(ahd, port+1) << 8)
	      | (ahd_inb(ahd, port+2) << 16)
	      | (ahd_inb(ahd, port+3) << 24)
	      | (((uint64_t)ahd_inb(ahd, port+4)) << 32)
	      | (((uint64_t)ahd_inb(ahd, port+5)) << 40)
	      | (((uint64_t)ahd_inb(ahd, port+6)) << 48)
	      | (((uint64_t)ahd_inb(ahd, port+7)) << 56));
}