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
struct tp_finger {int /*<<< orphan*/  abs_y; int /*<<< orphan*/  abs_x; } ;
struct applespi_data {void* tp_dim_max_y; void* tp_dim_min_y; void* tp_dim_max_x; void* tp_dim_min_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_int (int /*<<< orphan*/ ) ; 
 void* max (void*,int /*<<< orphan*/ ) ; 
 void* min (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void applespi_debug_update_dimensions(struct applespi_data *applespi,
					     const struct tp_finger *f)
{
	applespi->tp_dim_min_x = min(applespi->tp_dim_min_x,
				     le16_to_int(f->abs_x));
	applespi->tp_dim_max_x = max(applespi->tp_dim_max_x,
				     le16_to_int(f->abs_x));
	applespi->tp_dim_min_y = min(applespi->tp_dim_min_y,
				     le16_to_int(f->abs_y));
	applespi->tp_dim_max_y = max(applespi->tp_dim_max_y,
				     le16_to_int(f->abs_y));
}