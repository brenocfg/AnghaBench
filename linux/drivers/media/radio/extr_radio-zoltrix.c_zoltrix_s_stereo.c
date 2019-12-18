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
struct radio_isa_card {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int zoltrix_s_frequency (struct radio_isa_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zoltrix_s_stereo(struct radio_isa_card *isa, bool stereo)
{
	return zoltrix_s_frequency(isa, isa->freq);
}