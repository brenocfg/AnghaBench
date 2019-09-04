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
struct max3191x_chip {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ STATUS_BYTE_ENABLED ; 

__attribute__((used)) static unsigned int max3191x_wordlen(struct max3191x_chip *max3191x)
{
	return max3191x->mode == STATUS_BYTE_ENABLED ? 2 : 1;
}