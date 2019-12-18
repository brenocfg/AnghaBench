#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct maven_data {scalar_t__ version; TYPE_3__* primary_head; } ;
struct TYPE_4__ {int deflicker; } ;
struct TYPE_5__ {TYPE_1__ tvo_params; } ;
struct TYPE_6__ {TYPE_2__ altout; } ;

/* Variables and functions */
 scalar_t__ MGATVO_B ; 

__attribute__((used)) static unsigned char maven_compute_deflicker (const struct maven_data* md) {
	unsigned char df;
	
	df = (md->version == MGATVO_B?0x40:0x00);
	switch (md->primary_head->altout.tvo_params.deflicker) {
		case 0:
/*			df |= 0x00; */
			break;
		case 1:
			df |= 0xB1;
			break;
		case 2:
			df |= 0xA2;
			break;
	}
	return df;
}