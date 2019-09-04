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
struct TYPE_2__ {int /*<<< orphan*/  def_i2c_bus; int /*<<< orphan*/  is_webcam; int /*<<< orphan*/  has_msp34xx; } ;
struct em28xx {size_t model; TYPE_1__ board; int /*<<< orphan*/  def_i2c_bus; int /*<<< orphan*/  is_webcam; int /*<<< orphan*/  has_msp34xx; } ;

/* Variables and functions */
 TYPE_1__* em28xx_boards ; 
 int /*<<< orphan*/  em28xx_set_xclk_i2c_speed (struct em28xx*) ; 

__attribute__((used)) static inline void em28xx_set_model(struct em28xx *dev)
{
	dev->board = em28xx_boards[dev->model];
	dev->has_msp34xx = dev->board.has_msp34xx;
	dev->is_webcam = dev->board.is_webcam;

	em28xx_set_xclk_i2c_speed(dev);

	/* Should be initialized early, for I2C to work */
	dev->def_i2c_bus = dev->board.def_i2c_bus;
}