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
struct debug_view {int dummy; } ;
struct TYPE_3__ {int pages_per_area; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static int debug_prolog_pages_fn(debug_info_t *id, struct debug_view *view,
				 char *out_buf)
{
	return sprintf(out_buf, "%i\n", id->pages_per_area);
}