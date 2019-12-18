#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cmg_chars {scalar_t__* values; } ;
struct TYPE_2__ {scalar_t__* values; } ;
struct channel_path {TYPE_1__ cmg_chars; } ;

/* Variables and functions */
 int NR_MEASUREMENT_CHARS ; 

__attribute__((used)) static void
chsc_initialize_cmg_chars(struct channel_path *chp, u8 cmcv,
			  struct cmg_chars *chars)
{
	int i, mask;

	for (i = 0; i < NR_MEASUREMENT_CHARS; i++) {
		mask = 0x80 >> (i + 3);
		if (cmcv & mask)
			chp->cmg_chars.values[i] = chars->values[i];
		else
			chp->cmg_chars.values[i] = 0;
	}
}