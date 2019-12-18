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
struct soc_pcmcia_socket {size_t nr; } ;
struct scoop_pcmcia_dev {scalar_t__ keep_rd; int /*<<< orphan*/  keep_vs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power_ctrl ) (int /*<<< orphan*/ ,int,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NO_KEEP_VS ; 
 int /*<<< orphan*/  SCOOP_CPR ; 
 struct scoop_pcmcia_dev* SCOOP_DEV ; 
 TYPE_1__* platform_scoop_config ; 
 int /*<<< orphan*/  reset_scoop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  write_scoop_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sharpsl_pcmcia_init_reset(struct soc_pcmcia_socket *skt)
{
	struct scoop_pcmcia_dev *scoopdev = &SCOOP_DEV[skt->nr];

	reset_scoop(scoopdev->dev);

	/* Shared power controls need to be handled carefully */
	if (platform_scoop_config->power_ctrl)
		platform_scoop_config->power_ctrl(scoopdev->dev, 0x0000, skt->nr);
	else
		write_scoop_reg(scoopdev->dev, SCOOP_CPR, 0x0000);

	scoopdev->keep_vs = NO_KEEP_VS;
	scoopdev->keep_rd = 0;
}