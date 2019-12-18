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
struct vsc73xx {int /*<<< orphan*/  reset; int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

int vsc73xx_remove(struct vsc73xx *vsc)
{
	dsa_unregister_switch(vsc->ds);
	gpiod_set_value(vsc->reset, 1);

	return 0;
}