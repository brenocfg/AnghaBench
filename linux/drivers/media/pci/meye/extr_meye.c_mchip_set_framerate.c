#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  framerate; } ;
struct TYPE_4__ {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_HIC_S_RATE ; 
 int /*<<< orphan*/  mchip_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ meye ; 

__attribute__((used)) static void mchip_set_framerate(void)
{
	mchip_set(MCHIP_HIC_S_RATE, meye.params.framerate);
}