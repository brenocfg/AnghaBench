#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* counts; } ;
typedef  TYPE_1__ scsi_changer ;

/* Variables and functions */
 unsigned int CH_TYPES ; 

__attribute__((used)) static int
ch_checkrange(scsi_changer *ch, unsigned int type, unsigned int unit)
{
	if (type >= CH_TYPES  ||  unit >= ch->counts[type])
		return -1;
	return 0;
}