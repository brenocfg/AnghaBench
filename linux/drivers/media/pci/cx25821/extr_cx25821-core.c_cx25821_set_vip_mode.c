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
struct sram_channel {int /*<<< orphan*/  vip_ctl; int /*<<< orphan*/  pix_frmt; } ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIXEL_ENGINE_VIP1 ; 
 int /*<<< orphan*/  PIXEL_FRMT_422 ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx25821_set_vip_mode(struct cx25821_dev *dev,
				 const struct sram_channel *ch)
{
	cx_write(ch->pix_frmt, PIXEL_FRMT_422);
	cx_write(ch->vip_ctl, PIXEL_ENGINE_VIP1);
}