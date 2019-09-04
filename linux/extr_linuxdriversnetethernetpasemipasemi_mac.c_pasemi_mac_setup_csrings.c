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
struct pasemi_mac {scalar_t__ type; int /*<<< orphan*/  num_cs; void** cs; } ;

/* Variables and functions */
 scalar_t__ MAC_TYPE_XAUI ; 
 int MAX_CS ; 
 void* pasemi_mac_setup_csring (struct pasemi_mac*) ; 

__attribute__((used)) static void pasemi_mac_setup_csrings(struct pasemi_mac *mac)
{
	int i;
	mac->cs[0] = pasemi_mac_setup_csring(mac);
	if (mac->type == MAC_TYPE_XAUI)
		mac->cs[1] = pasemi_mac_setup_csring(mac);
	else
		mac->cs[1] = 0;

	for (i = 0; i < MAX_CS; i++)
		if (mac->cs[i])
			mac->num_cs++;
}