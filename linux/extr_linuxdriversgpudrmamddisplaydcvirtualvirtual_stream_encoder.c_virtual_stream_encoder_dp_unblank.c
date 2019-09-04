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
struct encoder_unblank_param {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void virtual_stream_encoder_dp_unblank(
	struct stream_encoder *enc,
	const struct encoder_unblank_param *param) {}