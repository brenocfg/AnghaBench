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
struct sp8870_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ sp8870_readreg (struct sp8870_state*,int) ; 

__attribute__((used)) static int sp8870_read_data_valid_signal(struct sp8870_state* state)
{
	return (sp8870_readreg(state, 0x0D02) > 0);
}