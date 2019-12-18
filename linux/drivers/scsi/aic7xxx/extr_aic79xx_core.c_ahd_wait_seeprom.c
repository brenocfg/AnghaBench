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
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int SEEARBACK ; 
 int SEEBUSY ; 
 int /*<<< orphan*/  SEESTAT ; 
 int /*<<< orphan*/  ahd_delay (int) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahd_wait_seeprom(struct ahd_softc *ahd)
{
	int cnt;

	cnt = 5000;
	while ((ahd_inb(ahd, SEESTAT) & (SEEARBACK|SEEBUSY)) != 0 && --cnt)
		ahd_delay(5);

	if (cnt == 0)
		return (ETIMEDOUT);
	return (0);
}