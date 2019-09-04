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
typedef  int uint8_t ;
struct da903x_chip {unsigned int events_mask; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9030_IRQ_MASK_A ; 
 int __da903x_writes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int da9030_unmask_events(struct da903x_chip *chip, unsigned int events)
{
	uint8_t v[3];

	chip->events_mask &= ~events;

	v[0] = (chip->events_mask & 0xff);
	v[1] = (chip->events_mask >> 8) & 0xff;
	v[2] = (chip->events_mask >> 16) & 0xff;

	return __da903x_writes(chip->client, DA9030_IRQ_MASK_A, 3, v);
}