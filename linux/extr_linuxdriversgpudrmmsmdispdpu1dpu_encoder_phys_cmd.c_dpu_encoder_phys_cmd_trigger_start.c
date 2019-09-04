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
struct dpu_encoder_phys {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_encoder_helper_trigger_start (struct dpu_encoder_phys*) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_trigger_start(
		struct dpu_encoder_phys *phys_enc)
{
	if (!phys_enc)
		return;

	dpu_encoder_helper_trigger_start(phys_enc);
}