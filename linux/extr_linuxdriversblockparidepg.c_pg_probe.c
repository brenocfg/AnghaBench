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
struct pg {int drive; } ;

/* Variables and functions */
 int pg_identify (struct pg*,int) ; 
 int /*<<< orphan*/  pg_reset (struct pg*) ; 

__attribute__((used)) static int pg_probe(struct pg *dev)
{
	if (dev->drive == -1) {
		for (dev->drive = 0; dev->drive <= 1; dev->drive++)
			if (!pg_reset(dev))
				return pg_identify(dev, 1);
	} else {
		if (!pg_reset(dev))
			return pg_identify(dev, 1);
	}
	return -1;
}