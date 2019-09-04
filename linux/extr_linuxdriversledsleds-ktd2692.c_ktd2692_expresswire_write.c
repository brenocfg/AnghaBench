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
typedef  int u8 ;
struct ktd2692_context {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ktd2692_expresswire_end (struct ktd2692_context*) ; 
 int /*<<< orphan*/  ktd2692_expresswire_set_bit (struct ktd2692_context*,int) ; 
 int /*<<< orphan*/  ktd2692_expresswire_start (struct ktd2692_context*) ; 

__attribute__((used)) static void ktd2692_expresswire_write(struct ktd2692_context *led, u8 value)
{
	int i;

	ktd2692_expresswire_start(led);
	for (i = 7; i >= 0; i--)
		ktd2692_expresswire_set_bit(led, value & BIT(i));
	ktd2692_expresswire_end(led);
}