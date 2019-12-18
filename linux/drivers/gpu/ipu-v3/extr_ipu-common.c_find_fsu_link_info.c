#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int chno; } ;
struct TYPE_3__ {int chno; } ;
struct fsu_link_info {TYPE_2__ sink; TYPE_1__ src; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fsu_link_info const*) ; 
 struct fsu_link_info const* fsu_link_info ; 

__attribute__((used)) static const struct fsu_link_info *find_fsu_link_info(int src, int sink)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fsu_link_info); i++) {
		if (src == fsu_link_info[i].src.chno &&
		    sink == fsu_link_info[i].sink.chno)
			return &fsu_link_info[i];
	}

	return NULL;
}