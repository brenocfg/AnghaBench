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
struct link_mst_stream_allocation_table {int dummy; } ;
struct link_encoder {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void virtual_link_encoder_update_mst_stream_allocation_table(
	struct link_encoder *enc,
	const struct link_mst_stream_allocation_table *table) {}