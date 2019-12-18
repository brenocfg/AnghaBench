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
struct st_data_s {int* is_registered; int /*<<< orphan*/  protos_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (void*,char*,int /*<<< orphan*/ ,char,char,char) ; 

void kim_st_list_protocols(struct st_data_s *st_gdata, void *buf)
{
	seq_printf(buf, "[%d]\nBT=%c\nFM=%c\nGPS=%c\n",
			st_gdata->protos_registered,
			st_gdata->is_registered[0x04] == true ? 'R' : 'U',
			st_gdata->is_registered[0x08] == true ? 'R' : 'U',
			st_gdata->is_registered[0x09] == true ? 'R' : 'U');
}