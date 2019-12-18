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
struct us_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** pba_to_lba; int /*<<< orphan*/ ** lba_to_pba; } ;

/* Variables and functions */
 TYPE_1__ MEDIA_INFO (struct us_data*) ; 
 int /*<<< orphan*/  alauda_read_map (struct us_data*,unsigned int) ; 

__attribute__((used)) static void alauda_ensure_map_for_zone(struct us_data *us, unsigned int zone)
{
	if (MEDIA_INFO(us).lba_to_pba[zone] == NULL
		|| MEDIA_INFO(us).pba_to_lba[zone] == NULL)
		alauda_read_map(us, zone);
}