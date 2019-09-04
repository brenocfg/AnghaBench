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
struct stream_encoder {int dummy; } ;
struct fixed31_32 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void virtual_stream_encoder_set_mst_bandwidth(
	struct stream_encoder *enc,
	struct fixed31_32 avg_time_slots_per_mtp) {}