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
 int /*<<< orphan*/  _dpu_encoder_phys_cmd_connect_te (struct dpu_encoder_phys*,int) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_prepare_idle_pc(
		struct dpu_encoder_phys *phys_enc)
{
	_dpu_encoder_phys_cmd_connect_te(phys_enc, false);
}