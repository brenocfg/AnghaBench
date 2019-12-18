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
struct cyclades_card {unsigned int num_chips; } ;

/* Variables and functions */

__attribute__((used)) static inline bool cy_is_Z(struct cyclades_card *card)
{
	return card->num_chips == (unsigned int)-1;
}