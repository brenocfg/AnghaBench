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
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
typedef  enum dpio_channel { ____Placeholder_dpio_channel } dpio_channel ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DPIO_CH0 ; 
 int DPIO_CH1 ; 
#define  PORT_B 130 
#define  PORT_C 129 
#define  PORT_D 128 

__attribute__((used)) static inline enum dpio_channel
vlv_dport_to_channel(struct intel_digital_port *dport)
{
	switch (dport->base.port) {
	case PORT_B:
	case PORT_D:
		return DPIO_CH0;
	case PORT_C:
		return DPIO_CH1;
	default:
		BUG();
	}
}