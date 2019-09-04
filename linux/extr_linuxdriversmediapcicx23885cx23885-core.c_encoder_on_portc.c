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
struct cx23885_dev {size_t board; } ;
struct TYPE_2__ {scalar_t__ portc; } ;

/* Variables and functions */
 scalar_t__ CX23885_MPEG_ENCODER ; 
 TYPE_1__* cx23885_boards ; 

__attribute__((used)) static inline int encoder_on_portc(struct cx23885_dev *dev)
{
	return cx23885_boards[dev->board].portc == CX23885_MPEG_ENCODER;
}