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
typedef  int /*<<< orphan*/  u16 ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 TYPE_1__* enc_to_intel_dsi (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u16 intel_dsi_encoder_ports(struct intel_encoder *encoder)
{
	return enc_to_intel_dsi(&encoder->base)->ports;
}