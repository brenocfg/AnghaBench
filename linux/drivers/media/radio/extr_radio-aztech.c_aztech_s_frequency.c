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
typedef  int /*<<< orphan*/  u32 ;
struct radio_isa_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aztech_set_pins ; 
 int /*<<< orphan*/  lm7000_set_freq (int /*<<< orphan*/ ,struct radio_isa_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aztech_s_frequency(struct radio_isa_card *isa, u32 freq)
{
	lm7000_set_freq(freq, isa, aztech_set_pins);

	return 0;
}