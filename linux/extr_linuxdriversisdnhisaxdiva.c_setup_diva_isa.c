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
struct IsdnCard {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int setup_diva_isa(struct IsdnCard *card)
{
	return (-1);	/* card not found; continue search */
}